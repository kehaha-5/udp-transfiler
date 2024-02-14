// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: file_down_msg.proto

#include "file_down_msg.pb.h"

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
PROTOBUF_CONSTEXPR FileDownMsg::FileDownMsg(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.data_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.startpos_)*/int64_t{0}
  , /*decltype(_impl_.size_)*/int64_t{0}} {}
struct FileDownMsgDefaultTypeInternal {
  PROTOBUF_CONSTEXPR FileDownMsgDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~FileDownMsgDefaultTypeInternal() {}
  union {
    FileDownMsg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 FileDownMsgDefaultTypeInternal _FileDownMsg_default_instance_;
}  // namespace proto
}  // namespace msg
static ::_pb::Metadata file_level_metadata_file_5fdown_5fmsg_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_file_5fdown_5fmsg_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_file_5fdown_5fmsg_2eproto = nullptr;

const uint32_t TableStruct_file_5fdown_5fmsg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownMsg, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownMsg, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownMsg, _impl_.startpos_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownMsg, _impl_.size_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::FileDownMsg, _impl_.data_),
  0,
  2,
  3,
  1,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, -1, sizeof(::msg::proto::FileDownMsg)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::msg::proto::_FileDownMsg_default_instance_._instance,
};

const char descriptor_table_protodef_file_5fdown_5fmsg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\023file_down_msg.proto\022\tmsg.proto\"I\n\013File"
  "DownMsg\022\014\n\004name\030\001 \002(\t\022\020\n\010startPos\030\002 \002(\003\022"
  "\014\n\004size\030\003 \001(\003\022\014\n\004data\030\004 \001(\014B\002H\002"
  ;
static ::_pbi::once_flag descriptor_table_file_5fdown_5fmsg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_file_5fdown_5fmsg_2eproto = {
    false, false, 111, descriptor_table_protodef_file_5fdown_5fmsg_2eproto,
    "file_down_msg.proto",
    &descriptor_table_file_5fdown_5fmsg_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_file_5fdown_5fmsg_2eproto::offsets,
    file_level_metadata_file_5fdown_5fmsg_2eproto, file_level_enum_descriptors_file_5fdown_5fmsg_2eproto,
    file_level_service_descriptors_file_5fdown_5fmsg_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_file_5fdown_5fmsg_2eproto_getter() {
  return &descriptor_table_file_5fdown_5fmsg_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_file_5fdown_5fmsg_2eproto(&descriptor_table_file_5fdown_5fmsg_2eproto);
namespace msg {
namespace proto {

// ===================================================================

class FileDownMsg::_Internal {
 public:
  using HasBits = decltype(std::declval<FileDownMsg>()._impl_._has_bits_);
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_startpos(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_size(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_data(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000005) ^ 0x00000005) != 0;
  }
};

FileDownMsg::FileDownMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:msg.proto.FileDownMsg)
}
FileDownMsg::FileDownMsg(const FileDownMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  FileDownMsg* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.name_){}
    , decltype(_impl_.data_){}
    , decltype(_impl_.startpos_){}
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
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_data()) {
    _this->_impl_.data_.Set(from._internal_data(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.startpos_, &from._impl_.startpos_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.size_) -
    reinterpret_cast<char*>(&_impl_.startpos_)) + sizeof(_impl_.size_));
  // @@protoc_insertion_point(copy_constructor:msg.proto.FileDownMsg)
}

inline void FileDownMsg::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.name_){}
    , decltype(_impl_.data_){}
    , decltype(_impl_.startpos_){int64_t{0}}
    , decltype(_impl_.size_){int64_t{0}}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

FileDownMsg::~FileDownMsg() {
  // @@protoc_insertion_point(destructor:msg.proto.FileDownMsg)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void FileDownMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
  _impl_.data_.Destroy();
}

void FileDownMsg::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void FileDownMsg::InternalSwap(FileDownMsg* other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::PROTOBUF_NAMESPACE_ID::Metadata FileDownMsg::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_file_5fdown_5fmsg_2eproto_getter, &descriptor_table_file_5fdown_5fmsg_2eproto_once,
      file_level_metadata_file_5fdown_5fmsg_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace msg
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::msg::proto::FileDownMsg*
Arena::CreateMaybeMessage< ::msg::proto::FileDownMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::msg::proto::FileDownMsg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
