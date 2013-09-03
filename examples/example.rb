#!/usr/bin/env ruby
$: << File.expand_path("../../lib", __FILE__)
$: << File.expand_path("../../ext", __FILE__)
require 'capn_proto'

ADDRESSBOOK_SCHEMA = File.expand_path("../addressbook.capnp", __FILE__);
MESSAGE = File.expand_path("../addressbook.bin", __FILE__);

module AddressBook extend CapnProto::SchemaLoader
  load_schema(ADDRESSBOOK_SCHEMA)
end

def print_address_book(file)
  addresses = AddressBook::AddressBook.read_from(file)

  addresses.people.each do |person|
    puts "#{person.name} : #{person.email}"
    person.phones.each do |phone|
      puts "#{phone.type} : #{phone.number}"
    end

    which = person.employment.which
    puts which

    if which == "unemployed"
      puts "unemployed"
    elsif which == 'employer'
      puts "employer: #{person.employment.employer}"
    elsif which == "school"
      puts "student at: #{person.employment.school}"
    elsif which == "selfEmployed"
      puts "self employed"
    end
  end
end

file = File.open(MESSAGE, "rb")
print_address_book(file)
