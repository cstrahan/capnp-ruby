#!/usr/bin/env python
import capnp
import subprocess

def loadSchema(file_name, cat_path='/bin/cat'):
    p = subprocess.Popen(['capnpc', '-o'+cat_path, file_name], stdout=subprocess.PIPE)
    retcode = p.wait()
    if retcode != 0:
        raise RuntimeError("capnpc failed for some reason")

    reader = capnp.schema.StreamFdMessageReader(p.stdout.fileno())
    request = reader.getRootCodeGeneratorRequest()
    return request 

schema = loadSchema("bootstrap/schema.capnp")

print schema
