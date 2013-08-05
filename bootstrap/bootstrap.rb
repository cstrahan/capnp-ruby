#!/usr/bin/env ruby
require 'shellwords'

SCHEMA = eval(File.read(File.expand_path("../schema.rb", __FILE__)))
LIB_SCHEMA = File.expand_path("../../lib/capn_proto/schema", __FILE__)
PRIMITIVE_TYPES = ['Bool','Int8','Int16','Int32','Int64','UInt8','UInt16',
                   'UInt32','UInt64','Float32','Float64']
BUILT_IN_TYPES = ['Bool','Int8','Int16','Int32','Int64','UInt8','UInt16',
                  'UInt32','UInt64','Float32','Float64', 'Text', 'Data', 
                  'Void', 'Object']

class String
  def undent
    indent = self.split("\n").select {|line| !line.strip.empty? }.map {|line| line.index(/[^\s]/) }.compact.min || 0
    self.gsub(/^[[:blank:]]{#{indent}}/, '')
  end

  def camelize(first_letter_in_uppercase = true)
    if first_letter_in_uppercase
      self.to_s.gsub(/\/(.?)/) { "::" + $1.upcase }.gsub(/(^|_)(.)/) { $2.upcase }
    else
      self.first + camelize(self)[1..-1]
    end
  end

  def underscore
    word = self.dup
    word.gsub!(/::/, '/')
    word.gsub!(/([A-Z]+)([A-Z][a-z])/,'\1_\2')
    word.gsub!(/([a-z\d])([A-Z])/,'\1_\2')
    word.tr!("-", "_")
    word.downcase!
    word
  end
end

class IndentedWriter
  attr_accessor :level

  def initialize
    @str   = ""
    @level = 0
  end

  def puts(str)
    if !str || str.empty?
      @str << "\n"
    else
      str.lines.each do |l|
        l = l.chomp
        if l.empty? || l =~ /^ +$/
          @str << "\n"
        else
          @str << "#{" "*level}#{l}\n"
        end
      end
    end
  end

  def indent(level=self.level+2)
    prev_level = self.level
    self.level = level
    yield
    self.level = prev_level
  end

  def to_s
    @str.dup
  end
end

def write_bool_member_getter(writer, member_name, member)
  bits = member['bits']
  byte_offset = ((bits[1])/8)
  mask = 2 ** (bits[1] % 8) # bits 1-8

  writer.puts "def get_#{member_name.underscore}()"
  writer.puts "  @builder.get_uchar(#{byte_offset}) & #{mask} == #{mask}"
  writer.puts "end"
end

def write_numeric_member_getter(writer, member_name, member)
  type = member['type']
  bits = member['bits']
  byte_offset = ((bits[0]+1)/8)

  writer.puts "def get_#{member_name.underscore}()"
  writer.puts "  @builder.get_#{type.underscore}(#{byte_offset})"
  writer.puts "end"
end

def write_member_getter(writer, member_name, member)
  type = member['type']
  return unless PRIMITIVE_TYPES.include?(type)

  if type == "Bool"
    write_bool_member_getter(writer, member_name, member)
    return
  elsif type == "union"
    writer.puts 
  else
    write_numeric_member_getter(writer, member_name, member)
  end
end

def write_struct(writer, name, node)
  writer.puts <<-CODE
module #{name}
  def self.bytes
    #{node['bytes']}
  end

  def self.pointers
    #{node['ptrs']}
  end

  class Reader
    def initialize(reader)
      @reader = reader
    end
  CODE
  # members
  node['members'].each do |member, member_node|
    next if member_node['type'] == 'struct'
    writer.puts ""
    writer.indent(writer.level + 4) do
      write_member_getter(writer, member, member_node)
    end
  end

  writer.puts "  end" # END BUILDER
  writer.puts <<-CODE
  class Builder
    def initialize(builder)
      @builder = builder
    end
  end
  CODE

  # structs
  node['members'].each do |member, member_node|
    if member_node['type'] == 'struct'
      writer.puts ""
      writer.indent do
        write_struct(writer, member, member_node)
      end
    end
  end

  writer.puts "end"
end

def main
  SCHEMA.keys.each do |k|
    writer = IndentedWriter.new
    writer.puts "module CapnProto"
    writer.puts "  module Schema"
    writer.indent(4) do
      write_struct(writer, k, SCHEMA[k])
    end
    writer.puts "  end"
    writer.puts "end"

    puts writer.to_s

    path = File.join(LIB_SCHEMA, "#{k.underscore}.rb")
    File.open(path, "w") do |f|
      f << writer.to_s
    end
  end
end

main()
