require 'spec_helper'
require 'capn_proto'

ADDRESSBOOK_SCHEMA = File.expand_path("../addressbook.capnp", __FILE__)

module AddressBook extend CapnProto::SchemaLoader
  load_schema(ADDRESSBOOK_SCHEMA)
end

describe "reading" do
  describe "Dynamic Structs" do
    let(:file) { open_file("addressbook.bin") }
    let(:addresses) { AddressBook::AddressBook.read_from(file) }

    it "unkown fields raise exception" do
      expect { addresses.foo }.to raise_error(CapnProto::Exception)
    end
  end

  describe "Dynamic Lists" do
    let(:file) { open_file("addressbook.bin") }
    let(:addresses) { AddressBook::AddressBook.read_from(file) }
    let(:people) { addresses.people }

    it "#[] given out-of-bounds index raises" do
      expect { addresses.people[999999] }.to raise_error(CapnProto::Exception)
    end
  end
end

describe "writing" do
  describe "Dynamic Structs" do
    let(:addresses) { AddressBook::AddressBook.new_message }

    it "works" do
      people = addresses.initPeople(3)
      bob = people.first
      bob.name = "Bob"
      bob.id = 10

      people[1] = bob
      x = people[1]
      puts x.name
      puts x.id
    end
  end
end
