{
  'Node' => { 
    'id'   => '0x96ae9bbee664c195',
    'type' => 'struct',
    'bytes' => 24,
    'ptrs'  => 4,
    'members' => {
      'id' => { 
        'ordinal' => 0,
        'type'    => 'UInt64',
        'bits'    => [0, 0],
      },
      'displayName' => { 
        'ordinal' => 1,
        'type'    => 'Text',
        'ptr'     => 0,
      },
      'displayNamePrefixLength' => { 
        'ordinal' => 12,
        'type'    => 'UInt32',
        'bits'    => [0, 160],
      },
      'scopeId' => { 
        'ordinal' => 2,
        'type'    => 'UInt6',
        'bits'    => [0, 64],
      },
      'nestedNodes' => { 
        'ordinal' => 3,
        'type'    => 'List(.Node.NestedNode)',
        'ptr'     => 1,
      },
      'NestedNode' => { 
        'id'   => '0xadfe8e889429ee28',
        'type' => 'struct',
        'bytes' => 8,
        'ptrs'  => 1,
        'members' => {
          'name' => { 
            'ordinal' => 0,
            'type'    => 'Text',
            'ptr'     => 0,
          },
          'id' => { 
            'ordinal' => 1,
            'type'    => 'UInt64',
            'bits'    => [0, 0],
          },
        }
      },
      'annotations' => { 
        'ordinal' => 4,
        'type'    => 'List(.Annotation)',
        'ptr'     => 2,
      },
      'body' => { 
        'id'   => '',
        'type' => 'union',
        'ordinal' => 5,
        'bits'    => [128, 144],
        'members' => {
          'fileNode' => { 
            'ordinal' => 6,
            'type'    => '.FileNode',
            'ptr'     => 3,
            'tag'     => 0,
          },
          'structNode' => { 
            'ordinal' => 7,
            'type'    => '.StructNode',
            'ptr'     => 3,
            'tag'     => 1,
          },
          'enumNode' => { 
            'ordinal' => 8,
            'type'    => '.EnumNode',
            'ptr'     => 3,
            'tag'     => 2,
          },
          'interfaceNode' => { 
            'ordinal' => 9,
            'type'    => '.InterfaceNode',
            'ptr'     => 3,
            'tag'     => 3,
          },
          'constNode' => { 
            'ordinal' => 10,
            'type'    => '.ConstNode',
            'ptr'     => 3,
            'tag'     => 4,
          },
          'annotationNode' => { 
            'ordinal' => 11,
            'type'    => '.AnnotationNode',
            'ptr'     => 3,
            'tag'     => 5,
          },
        }
      },
    }
  },
  'Type' => { 
    'id'   => '0xdddca9a9ee299e42',
    'type' => 'struct',
    'bytes' => 16,
    'ptrs'  => 1,
    'members' => {
      'body' => { 
        'id'   => '',
        'type' => 'union',
        'ordinal' => 0,
        'bits'    => [0, 16],
        'members' => {
          'voidType' => { 
            'ordinal' => 1,
            'type'    => 'Void',
            'tag'     => 0,
          },
          'boolType' => { 
            'ordinal' => 2,
            'type'    => 'Void',
            'tag'     => 1,
          },
          'int8Type' => { 
            'ordinal' => 3,
            'type'    => 'Void',
            'tag'     => 2,
          },
          'int16Type' => { 
            'ordinal' => 4,
            'type'    => 'Void',
            'tag'     => 3,
          },
          'int32Type' => { 
            'ordinal' => 5,
            'type'    => 'Void',
            'tag'     => 4,
          },
          'int64Type' => { 
            'ordinal' => 6,
            'type'    => 'Void',
            'tag'     => 5,
          },
          'uint8Type' => { 
            'ordinal' => 7,
            'type'    => 'Void',
            'tag'     => 6,
          },
          'uint16Type' => { 
            'ordinal' => 8,
            'type'    => 'Void',
            'tag'     => 7,
          },
          'uint32Type' => { 
            'ordinal' => 9,
            'type'    => 'Void',
            'tag'     => 8,
          },
          'uint64Type' => { 
            'ordinal' => 10,
            'type'    => 'Void',
            'tag'     => 9,
          },
          'float32Type' => { 
            'ordinal' => 11,
            'type'    => 'Void',
            'tag'     => 10,
          },
          'float64Type' => { 
            'ordinal' => 12,
            'type'    => 'Void',
            'tag'     => 11,
          },
          'textType' => { 
            'ordinal' => 13,
            'type'    => 'Void',
            'tag'     => 12,
          },
          'dataType' => { 
            'ordinal' => 14,
            'type'    => 'Void',
            'tag'     => 13,
          },
          'listType' => { 
            'ordinal' => 15,
            'type'    => '.Type',
            'ptr'     => 0,
            'tag'     => 14,
          },
          'enumType' => { 
            'ordinal' => 16,
            'type'    => 'UInt64',
            'bits'    => [0, 64],
            'tag'     => 15,
          },
          'structType' => { 
            'ordinal' => 17,
            'type'    => 'UInt64',
            'bits'    => [0, 64],
            'tag'     => 16,
          },
          'interfaceType' => { 
            'ordinal' => 18,
            'type'    => 'UInt64',
            'bits'    => [0, 64],
            'tag'     => 17,
          },
          'objectType' => { 
            'ordinal' => 19,
            'type'    => 'Void',
            'tag'     => 18,
          },
        }
      },
    }
  },
  'Value' => { 
    'id'   => '0xc2c768aee22269ee',
    'type' => 'struct',
    'bytes' => 16,
    'ptrs'  => 1,
    'members' => {
      'body' => { 
        'id'   => '',
        'type' => 'union',
        'ordinal' => 0,
        'bits'    => [0, 16],
        'members' => {
          'voidValue' => { 
            'ordinal' => 10,
            'type'    => 'Void',
            'tag'     => 9,
          },
          'boolValue' => { 
            'ordinal' => 2,
            'type'    => 'Bool',
            'bits'    => [0, 64],
            'tag'     => 1,
          },
          'int8Value' => { 
            'ordinal' => 3,
            'type'    => 'Int8',
            'bits'    => [0, 64],
            'tag'     => 2,
          },
          'int16Value' => { 
            'ordinal' => 4,
            'type'    => 'Int16',
            'bits'    => [0, 64],
            'tag'     => 3,
          },
          'int32Value' => { 
            'ordinal' => 5,
            'type'    => 'Int32',
            'bits'    => [0, 64],
            'tag'     => 4,
          },
          'int64Value' => { 
            'ordinal' => 6,
            'type'    => 'Int64',
            'bits'    => [0, 64],
            'tag'     => 5,
          },
          'uint8Value' => { 
            'ordinal' => 7,
            'type'    => 'UInt8',
            'bits'    => [0, 64],
            'tag'     => 6,
          },
          'uint16Value' => { 
            'ordinal' => 8,
            'type'    => 'UInt16',
            'bits'    => [0, 64],
            'tag'     => 7,
          },
          'uint32Value' => { 
            'ordinal' => 9,
            'type'    => 'UInt32',
            'bits'    => [0, 64],
            'tag'     => 8,
          },
          'uint64Value' => { 
            'ordinal' => 1,
            'type'    => 'UInt64',
            'bits'    => [0, 64],
            'tag'     => 0,
          },
          'float32Value' => { 
            'ordinal' => 11,
            'type'    => 'Float32',
            'bits'    => [0, 64],
            'tag'     => 10,
          },
          'float64Value' => { 
            'ordinal' => 12,
            'type'    => 'Float64',
            'bits'    => [0, 64],
            'tag'     => 11,
          },
          'textValue' => { 
            'ordinal' => 13,
            'type'    => 'Text',
            'ptr'     => 0,
            'tag'     => 12,
          },
          'dataValue' => { 
            'ordinal' => 14,
            'type'    => 'Data',
            'ptr'     => 0,
            'tag'     => 13,
          },
          'listValue' => { 
            'ordinal' => 15,
            'type'    => 'Object',
            'ptr'     => 0,
            'tag'     => 14,
          },
          'enumValue' => { 
            'ordinal' => 16,
            'type'    => 'UInt16',
            'bits'    => [0, 64],
            'tag'     => 15,
          },
          'structValue' => { 
            'ordinal' => 17,
            'type'    => 'Object',
            'ptr'     => 0,
            'tag'     => 16,
          },
          'interfaceValue' => { 
            'ordinal' => 18,
            'type'    => 'Void',
            'tag'     => 17,
          },
          'objectValue' => { 
            'ordinal' => 19,
            'type'    => 'Object',
            'ptr'     => 0,
            'tag'     => 18,
          },
        }
      },
    }
  },
  'Annotation' => { 
    'id'   => '0xdb785131c0cfee73',
    'type' => 'struct',
    'bytes' => 8,
    'ptrs'  => 1,
    'members' => {
      'id' => { 
        'ordinal' => 0,
        'type'    => 'UInt64',
        'bits'    => [0, 0],
      },
      'value' => { 
        'ordinal' => 1,
        'type'    => '.Value',
        'ptr'     => 0,
      },
    }
  },
  'FileNode' => { 
    'id'   => '0xd59c380b31b76b1f',
    'type' => 'struct',
    'bytes' => 0,
    'ptrs'  => 1,
    'members' => {
      'imports' => { 
        'ordinal' => 0,
        'type'    => 'List(.FileNode.Import)',
        'ptr'     => 0,
      },
      'Import' => { 
        'id'   => '0xd5d6a9044d63c158',
        'type' => 'struct',
        'bytes' => 8,
        'ptrs'  => 1,
        'members' => {
          'id' => { 
            'ordinal' => 0,
            'type'    => 'UInt64',
            'bits'    => [0, 0],
          },
          'name' => { 
            'ordinal' => 1,
            'type'    => 'Text',
            'ptr'     => 0,
          },
        }
      },
    }
  },
  'ElementSize' => { 
    'id'   => '0xd7326bd22e1c298c',
    'type' => 'enum',
    'members' => {
      'empty ' => { 
        'ordinal' => 0,
        'type'    => '@0',
      },
      'bit ' => { 
        'ordinal' => 1,
        'type'    => '@1',
      },
      'byte ' => { 
        'ordinal' => 2,
        'type'    => '@2',
      },
      'twoBytes ' => { 
        'ordinal' => 3,
        'type'    => '@3',
      },
      'fourBytes ' => { 
        'ordinal' => 4,
        'type'    => '@4',
      },
      'eightBytes ' => { 
        'ordinal' => 5,
        'type'    => '@5',
      },
      'pointer ' => { 
        'ordinal' => 6,
        'type'    => '@6',
      },
      'inlineComposite ' => { 
        'ordinal' => 7,
        'type'    => '@7',
      },
    }
  },
  'StructNode' => { 
    'id'   => '0xbf81d92a0b7e0c1f',
    'type' => 'struct',
    'bytes' => 8,
    'ptrs'  => 1,
    'members' => {
      'dataSectionWordSize' => { 
        'ordinal' => 0,
        'type'    => 'UInt16',
        'bits'    => [0, 0],
      },
      'pointerSectionSize' => { 
        'ordinal' => 1,
        'type'    => 'UInt16',
        'bits'    => [0, 16],
      },
      'preferredListEncoding' => { 
        'ordinal' => 2,
        'type'    => '.ElementSize',
        'bits'    => [0, 32],
      },
      'members' => { 
        'ordinal' => 3,
        'type'    => 'List(.StructNode.Member)',
        'ptr'     => 0,
      },
      'Member' => { 
        'id'   => '0x9a2db4bd6b74f8c1',
        'type' => 'struct',
        'bytes' => 8,
        'ptrs'  => 3,
        'members' => {
          'name' => { 
            'ordinal' => 0,
            'type'    => 'Text',
            'ptr'     => 0,
          },
          'ordinal' => { 
            'ordinal' => 1,
            'type'    => 'UInt16',
            'bits'    => [0, 0],
          },
          'codeOrder' => { 
            'ordinal' => 2,
            'type'    => 'UInt16',
            'bits'    => [0, 16],
          },
          'annotations' => { 
            'ordinal' => 3,
            'type'    => 'List(.Annotation)',
            'ptr'     => 1,
          },
          'body' => { 
            'id'   => '',
            'type' => 'union',
            'ordinal' => 4,
            'bits'    => [32, 48],
            'members' => {
              'fieldMember' => { 
                'ordinal' => 5,
                'type'    => '.StructNode.Field',
                'ptr'     => 2,
                'tag'     => 0,
              },
              'unionMember' => { 
                'ordinal' => 6,
                'type'    => '.StructNode.Union',
                'ptr'     => 2,
                'tag'     => 1,
              },
              'groupMember' => { 
                'ordinal' => 7,
                'type'    => '.StructNode.Group',
                'ptr'     => 2,
                'tag'     => 2,
              },
            }
          },
        }
      },
      'Field' => { 
        'id'   => '0xc75846e17057a41f',
        'type' => 'struct',
        'bytes' => 4,
        'ptrs'  => 2,
        'members' => {
          'offset' => { 
            'ordinal' => 0,
            'type'    => 'UInt32',
            'bits'    => [0, 0],
          },
          'type' => { 
            'ordinal' => 1,
            'type'    => '.Type',
            'ptr'     => 0,
          },
          'defaultValue' => { 
            'ordinal' => 2,
            'type'    => '.Value',
            'ptr'     => 1,
          },
        }
      },
      'Union' => { 
        'id'   => '0xefff479ae161da06',
        'type' => 'struct',
        'bytes' => 4,
        'ptrs'  => 1,
        'members' => {
          'discriminantOffset' => { 
            'ordinal' => 0,
            'type'    => 'UInt32',
            'bits'    => [0, 0],
          },
          'members' => { 
            'ordinal' => 1,
            'type'    => 'List(.StructNode.Member)',
            'ptr'     => 0,
          },
        }
      },
      'Group' => { 
        'id'   => '0xac91947f51b055ed',
        'type' => 'struct',
        'bytes' => 0,
        'ptrs'  => 1,
        'members' => {
          'members' => { 
            'ordinal' => 0,
            'type'    => 'List(.StructNode.Member)',
            'ptr'     => 0,
          },
        }
      },
    }
  },
  'EnumNode' => { 
    'id'   => '0xd612f44d78962abf',
    'type' => 'struct',
    'bytes' => 0,
    'ptrs'  => 1,
    'members' => {
      'enumerants' => { 
        'ordinal' => 0,
        'type'    => 'List(.EnumNode.Enumerant)',
        'ptr'     => 0,
      },
      'Enumerant' => { 
        'id'   => '0xc9ac441973b9f177',
        'type' => 'struct',
        'bytes' => 2,
        'ptrs'  => 2,
        'members' => {
          'name' => { 
            'ordinal' => 0,
            'type'    => 'Text',
            'ptr'     => 0,
          },
          'codeOrder' => { 
            'ordinal' => 1,
            'type'    => 'UInt16',
            'bits'    => [0, 0],
          },
          'annotations' => { 
            'ordinal' => 2,
            'type'    => 'List(.Annotation)',
            'ptr'     => 1,
          },
        }
      },
    }
  },
  'InterfaceNode' => { 
    'id'   => '0xb8a6ecfa2d5121e6',
    'type' => 'struct',
    'bytes' => 0,
    'ptrs'  => 1,
    'members' => {
      'methods' => { 
        'ordinal' => 0,
        'type'    => 'List(.InterfaceNode.Method)',
        'ptr'     => 0,
      },
      'Method' => { 
        'id'   => '0xbdd7f6f0832387ac',
        'type' => 'struct',
        'bytes' => 4,
        'ptrs'  => 4,
        'members' => {
          'name' => { 
            'ordinal' => 0,
            'type'    => 'Text',
            'ptr'     => 0,
          },
          'codeOrder' => { 
            'ordinal' => 1,
            'type'    => 'UInt16',
            'bits'    => [0, 0],
          },
          'params' => { 
            'ordinal' => 2,
            'type'    => 'List(.InterfaceNode.Method.Param)',
            'ptr'     => 1,
          },
          'Param' => { 
            'id'   => '0xd6d38cf4e366e91c',
            'type' => 'struct',
            'bytes' => 0,
            'ptrs'  => 4,
            'members' => {
              'name' => { 
                'ordinal' => 0,
                'type'    => 'Text',
                'ptr'     => 0,
              },
              'type' => { 
                'ordinal' => 1,
                'type'    => '.Type',
                'ptr'     => 1,
              },
              'defaultValue' => { 
                'ordinal' => 2,
                'type'    => '.Value',
                'ptr'     => 2,
              },
              'annotations' => { 
                'ordinal' => 3,
                'type'    => 'List(.Annotation)',
                'ptr'     => 3,
              },
            }
          },
          'requiredParamCount' => { 
            'ordinal' => 3,
            'type'    => 'UInt16',
            'bits'    => [0, 16],
          },
          'returnType' => { 
            'ordinal' => 4,
            'type'    => '.Type',
            'ptr'     => 2,
          },
          'annotations' => { 
            'ordinal' => 5,
            'type'    => 'List(.Annotation)',
            'ptr'     => 3,
          },
        }
      },
    }
  },
  'ConstNode' => { 
    'id'   => '0x8f0cf892b24a8062',
    'type' => 'struct',
    'bytes' => 0,
    'ptrs'  => 2,
    'members' => {
      'type' => { 
        'ordinal' => 0,
        'type'    => '.Type',
        'ptr'     => 0,
      },
      'value' => { 
        'ordinal' => 1,
        'type'    => '.Value',
        'ptr'     => 1,
      },
    }
  },
  'AnnotationNode' => { 
    'id'   => '0xf386f41ae9f5cbe5',
    'type' => 'struct',
    'bytes' => 2,
    'ptrs'  => 1,
    'members' => {
      'type' => { 
        'ordinal' => 0,
        'type'    => '.Type',
        'ptr'     => 0,
      },
      'targetsFile' => { 
        'ordinal' => 1,
        'type'    => 'Bool',
        'bits'    => [0, 0],
      },
      'targetsConst' => { 
        'ordinal' => 2,
        'type'    => 'Bool',
        'bits'    => [0, 1],
      },
      'targetsEnum' => { 
        'ordinal' => 3,
        'type'    => 'Bool',
        'bits'    => [0, 2],
      },
      'targetsEnumerant' => { 
        'ordinal' => 4,
        'type'    => 'Bool',
        'bits'    => [0, 3],
      },
      'targetsStruct' => { 
        'ordinal' => 5,
        'type'    => 'Bool',
        'bits'    => [0, 4],
      },
      'targetsField' => { 
        'ordinal' => 6,
        'type'    => 'Bool',
        'bits'    => [0, 5],
      },
      'targetsUnion' => { 
        'ordinal' => 7,
        'type'    => 'Bool',
        'bits'    => [0, 6],
      },
      'targetsInterface' => { 
        'ordinal' => 8,
        'type'    => 'Bool',
        'bits'    => [0, 7],
      },
      'targetsMethod' => { 
        'ordinal' => 9,
        'type'    => 'Bool',
        'bits'    => [0, 8],
      },
      'targetsParam' => { 
        'ordinal' => 10,
        'type'    => 'Bool',
        'bits'    => [0, 9],
      },
      'targetsAnnotation' => { 
        'ordinal' => 11,
        'type'    => 'Bool',
        'bits'    => [0, 10],
      },
    }
  },
  'CodeGeneratorRequest' => { 
    'id'   => '0xd095654a26e15f1d',
    'type' => 'struct',
    'bytes' => 0,
    'ptrs'  => 2,
    'members' => {
      'nodes' => { 
        'ordinal' => 0,
        'type'    => 'List(.Node)',
        'ptr'     => 0,
      },
      'requestedFiles' => { 
        'ordinal' => 1,
        'type'    => 'List(UInt64)',
        'ptr'     => 1,
      },
    }
  },
}
