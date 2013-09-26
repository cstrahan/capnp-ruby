require 'tempfile'
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
  describe "#write" do
    it "full circle" do
      tmp = Tempfile.new('test.bin')
      addresses = AddressBook::AddressBook.new_message
      people = addresses.initPeople(1)
      bob = people[0]
      bob.name = "Bob"
      bob.id = 123
      addresses.write(tmp)

      tmp.rewind
      addresses = AddressBook::AddressBook.read_from(tmp)
      expect(addresses.people.size).to eq 1
      expect(addresses.people.first.name).to eq "Bob"
      expect(addresses.people.first.id).to eq 123
    end
  end

  describe "#to_bytes" do
    it "full circle" do
      addresses = AddressBook::AddressBook.new_message
      people = addresses.initPeople(1)
      bob = people[0]
      bob.name = "Bob"
      bob.id = 123
      bytes = addresses.to_bytes

      addresses = AddressBook::AddressBook.make_from_bytes(bytes)
      expect(addresses.people.size).to eq 1
      expect(addresses.people.first.name).to eq "Bob"
      expect(addresses.people.first.id).to eq 123
    end
  end

  describe "Dynamic Structs" do
    let(:addresses) { AddressBook::AddressBook.new_message }

    it "works" do
      people = addresses.initPeople(3)
      bob = people.first
      bob.name = "Bob"
      bob.id = 10

      people[1] = bob
      x = people[1]
    end
  end
end
