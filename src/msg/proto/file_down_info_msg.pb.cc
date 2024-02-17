// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: file_down_info_msg.proto

#include "file_down_info_msg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace msg {
namespace proto {
PROTOBUF_CONSTEXPR fileDownInfo::fileDownInfo(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.hash_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.humanreadablesize_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.size_)*/uint64_t{0u}} {}
struct fileDownInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR fileDownInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~fileDownInfoDefaultTypeInternal() {}
  union {
    fileDownInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 fileDownInfoDefaultTypeInternal _fileDownInfo_default_instance_;
PROTOBUF_CONSTEXPR FileDownInfoMsg::FileDownInfoMsg(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.fileinfos_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct FileDownInfoMsgDefaultTypeInternal {
  PROTOBUF_CONSTEXPR FileDownInfoMsgDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~FileDownInfoMsgDefaultTypeInternal() {}
  union {
    FileDownInfoMsg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 FileDownInfoMsgDefaultTypeInternal _FileDownInfoMsg_default_instance_;
}  // namespace proto
}  // namespace msg
static ::_pb::Metadata file_level_metadata_file_5fdown_5finfo_5fmsg_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_file_5fdown_5finfo_5fmsg_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_file_5fdown_5finfo_5fmsg_2eproto = nullptr;

const uint32_t TableStruct_file_5fdown_5finfo_5fmsg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::msg::proto::fileDownInfo, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::fileDownInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::msg::proto::fileDownInfo, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::fileDownInfo, _impl_.size_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::fileDownInfo, _impl_.hash_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::fileDownInfo, _impl_.humanreadablesize_),
  0,
  3,
  1,
  2,
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownInfoMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownInfoMsg, _impl_.fileinfos_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, -1, sizeof(::msg::proto::fileDownInfo)},
  { 14, -1, -1, sizeof(::msg::proto::FileDownInfoMsg)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::msg::proto::_fileDownInfo_default_instance_._instance,
  &::msg::proto::_FileDownInfoMsg_default_instance_._instance,
};

const char descriptor_table_protodef_file_5fdown_5finfo_5fmsg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030file_down_info_msg.proto\022\tmsg.proto\"S\n"
  "\014fileDownInfo\022\014\n\004name\030\001 \002(\t\022\014\n\004size\030\002 \002("
  "\004\022\014\n\004hash\030\003 \002(\t\022\031\n\021humanReadableSize\030\004 \002"
  "(\t\"=\n\017FileDownInfoMsg\022*\n\tfileinfos\030\001 \003(\013"
  "2\027.msg.proto.fileDownInfoB\002H\002"
  ;
static ::_pbi::once_flag descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_file_5fdown_5finfo_5fmsg_2eproto = {
    false, false, 189, descriptor_table_protodef_file_5fdown_5finfo_5fmsg_2eproto,
    "file_down_info_msg.proto",
    &descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_file_5fdown_5finfo_5fmsg_2eproto::offsets,
    file_level_metadata_file_5fdown_5finfo_5fmsg_2eproto, file_level_enum_descriptors_file_5fdown_5finfo_5fmsg_2eproto,
    file_level_service_descriptors_file_5fdown_5finfo_5fmsg_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_getter() {
  return &descriptor_table_file_5fdown_5finfo_5fmsg_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_file_5fdown_5finfo_5fmsg_2eproto(&descriptor_table_file_5fdown_5finfo_5fmsg_2eproto);
namespace msg {
namespace proto {

// ===================================================================

class fileDownInfo::_Internal {
 public:
  using HasBits = decltype(std::declval<fileDownInfo>()._impl_._has_bits_);
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_size(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_hash(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_humanreadablesize(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x0000000f) ^ 0x0000000f) != 0;
  }
};

fileDownInfo::fileDownInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:msg.proto.fileDownInfo)
}
fileDownInfo::fileDownInfo(const fileDownInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  fileDownInfo* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.name_){}
    , decltype(_impl_.hash_){}
    , decltype(_impl_.humanreadablesize_){}
    , decltype(_impl_.size_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_name()) {
    _this->_impl_.name_.Set(from._internal_name(), 
      _this->GetArenaForAllocation());
  }
  _impl_.hash_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.hash_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_hash()) {
    _this->_impl_.hash_.Set(from._internal_hash(), 
      _this->GetArenaForAllocation());
  }
  _impl_.humanreadablesize_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.humanreadablesize_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_humanreadablesize()) {
    _this->_impl_.humanreadablesize_.Set(from._internal_humanreadablesize(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.size_ = from._impl_.size_;
  // @@protoc_insertion_point(copy_constructor:msg.proto.fileDownInfo)
}

inline void fileDownInfo::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.name_){}
    , decltype(_impl_.hash_){}
    , decltype(_impl_.humanreadablesize_){}
    , decltype(_impl_.size_){uint64_t{0u}}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.hash_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.hash_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.humanreadablesize_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.humanreadablesize_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

fileDownInfo::~fileDownInfo() {
  // @@protoc_insertion_point(destructor:msg.proto.fileDownInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void fileDownInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
  _impl_.hash_.Destroy();
  _impl_.humanreadablesize_.Destroy();
}

void fileDownInfo::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void fileDownInfo::InternalSwap(fileDownInfo* other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::PROTOBUF_NAMESPACE_ID::Metadata fileDownInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_getter, &descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_once,
      file_level_metadata_file_5fdown_5finfo_5fmsg_2eproto[0]);
}

// ===================================================================

class FileDownInfoMsg::_Internal {
 public:
};

FileDownInfoMsg::FileDownInfoMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:msg.proto.FileDownInfoMsg)
}
FileDownInfoMsg::FileDownInfoMsg(const FileDownInfoMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  FileDownInfoMsg* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.fileinfos_){from._impl_.fileinfos_}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:msg.proto.FileDownInfoMsg)
}

inline void FileDownInfoMsg::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.fileinfos_){arena}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

FileDownInfoMsg::~FileDownInfoMsg() {
  // @@protoc_insertion_point(destructor:msg.proto.FileDownInfoMsg)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void FileDownInfoMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.fileinfos_.~RepeatedPtrField();
}

void FileDownInfoMsg::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void FileDownInfoMsg::InternalSwap(FileDownInfoMsg* other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::PROTOBUF_NAMESPACE_ID::Metadata FileDownInfoMsg::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_getter, &descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_once,
      file_level_metadata_file_5fdown_5finfo_5fmsg_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace msg
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::msg::proto::fileDownInfo*
Arena::CreateMaybeMessage< ::msg::proto::fileDownInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::msg::proto::fileDownInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::msg::proto::FileDownInfoMsg*
Arena::CreateMaybeMessage< ::msg::proto::FileDownInfoMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::msg::proto::FileDownInfoMsg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>