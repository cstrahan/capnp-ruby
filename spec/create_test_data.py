#!/usr/bin/env python
from __future__ import print_function
import os
import capnp

this_dir = os.path.dirname(__file__)
addressbook = capnp.load(os.path.join(this_dir, 'addressbook.capnp'))

def writeAddressBook(file):
    addresses = addressbook.AddressBook.newMessage()
    people = addresses.init('people', 2)

    alice = people[0]
    alice.id = 123
    alice.name = 'Alice'
    alice.email = 'alice@example.com'
    alicePhones = alice.init('phones', 1)
    alicePhones[0].number = "555-1212"
    alicePhones[0].type = 'mobile'
    alice.employment.school = "MIT"

    bob = people[1]
    bob.id = 456
    bob.name = 'Bob'
    bob.email = 'bob@example.com'
    bobPhones = bob.init('phones', 2)
    bobPhones[0].number = "555-4567"
    bobPhones[0].type = 'home'
    bobPhones[1].number = "555-7654"
    bobPhones[1].type = 'work'
    bob.employment.unemployed = None

    addresses.writeTo(file)


if __name__ == '__main__':
    f = open('addressbook.bin', 'w')
    writeAddressBook(f)
