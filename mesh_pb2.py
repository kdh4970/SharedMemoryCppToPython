# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: mesh.proto
# Protobuf Python Version: 4.26.0-dev
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\nmesh.proto\"\x1a\n\x06Vertex\x12\x10\n\x08position\x18\x01 \x03(\x02\"\"\n\x08Triangle\x12\x16\n\x0evertex_indices\x18\x01 \x03(\x05\"S\n\x04Mesh\x12\x12\n\nclass_info\x18\x01 \x01(\t\x12\x19\n\x08vertices\x18\x02 \x03(\x0b\x32\x07.Vertex\x12\x1c\n\ttriangles\x18\x03 \x03(\x0b\x32\t.Triangleb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'mesh_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._loaded_options = None
  _globals['_VERTEX']._serialized_start=14
  _globals['_VERTEX']._serialized_end=40
  _globals['_TRIANGLE']._serialized_start=42
  _globals['_TRIANGLE']._serialized_end=76
  _globals['_MESH']._serialized_start=78
  _globals['_MESH']._serialized_end=161
# @@protoc_insertion_point(module_scope)