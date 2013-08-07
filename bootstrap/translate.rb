#!/usr/bin/env ruby
require 'shellwords'

WORD_SIZE = 8
POINTER_SIZE = WORD_SIZE

schema_def = File.expand_path("../schema.capnp", __FILE__)
dump = `capnpc -v #{schema_def.shellescape}`
lines = dump.lines.map(&:chomp)
lines = lines.drop_while {|line| !line.start_with?("struct Node")}

puts("{")
lines.each do |line|
  sline = line.strip

  if line == ''
    next
  elsif ['struct', 'union', 'enum'].include?(sline.split(" ")[0])
    name  = sline.split(" ")[1]
    type  = sline.split(" ")[0]
    id    = sline.split(" ")[2][1..-1]

    if sline.start_with?("struct")
      match    = /(\d+) bytes, (\d+) pointers/.match(sline)
      bytes    = match[1].to_i
      pointers = match[2].to_i
    end

    if match = /\[(\d+), (\d+)\)/.match(sline)
      bit_begin = match[1].to_i
      bit_len   = match[2].to_i
    end

    if name.include?("@")
      ordinal   = name.split("@")[1].to_i
      name      = name.split("@")[0]
    end

    puts("'%s' => { " % name)
    puts("  'id'   => '%s'," % id)
    puts("  'type' => '%s'," % type)
    if bytes
      puts("  'bytes' => %i," % bytes)
      puts("  'ptrs'  => %i," % pointers)
    end
    if bit_begin
      puts("  'bits'    => [%i, %i]," % [bit_begin, bit_len])
    end
    if ordinal
      puts("  'ordinal' => %i," % ordinal)
    end
    puts("  'members' => {" % [name, type])
  elsif sline.start_with?('}')
    puts("  }")
    puts("},")
  else
    name    = sline.split("@")[0]
    ordinal = sline.split("@")[1].to_i
    type    = sline.split(" ")[1][0..-2]

    puts("    '%s' => { " % name)
    puts("      'ordinal' => %i," % ordinal)
    puts("      'type'    => '%s'," % type)
    if match = /\[(\d+), (\d+)\)/.match(sline)
      bit_begin = match[1].to_i
      bit_len   = match[2].to_i
      puts("      'bits'    => [%i, %i]," % [bit_begin, bit_len])
    elsif match = /ptr\[(\d+)\]/.match(sline)
      ptr_no = match[1].to_i
      puts("      'ptr'     => %i," % ptr_no)
    end

    if match = /tag = (\d+)/.match(sline)
      tag_no = match[1].to_i
      puts("      'tag'     => %i," % tag_no)
    end

    puts("    },")
  end
end
puts("}")
