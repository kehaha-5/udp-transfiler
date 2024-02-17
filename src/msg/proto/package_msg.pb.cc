// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: package_msg.proto

#include "package_msg.pb.h"

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
PROTOBUF_CONSTEXPR PackageMsg::PackageMsg(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.data_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.ack_)*/uint64_t{0u}
  , /*decltype(_impl_.order_)*/0u
  , /*decltype(_impl_.datalen_)*/0u
  , /*decltype(_impl_.tatolszie_)*/0u
  , /*decltype(_impl_.msgtype_)*/1} {}
struct PackageMsgDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PackageMsgDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PackageMsgDefaultTypeInternal() {}
  union {
    PackageMsg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PackageMsgDefaultTypeInternal _PackageMsg_default_instance_;
}  // namespace proto
}  // namespace msg
static ::_pb::Metadata file_level_metadata_package_5fmsg_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_package_5fmsg_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_package_5fmsg_2eproto = nullptr;

const uint32_t TableStruct_package_5fmsg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_.ack_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_.order_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_.datalen_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_.tatolszie_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_.msgtype_),
  PROTOBUF_FIELD_OFFSET(::msg::proto::PackageMsg, _impl_.data_),
  1,
  2,
  3,
  4,
  5,
  0,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 12, -1, sizeof(::msg::proto::PackageMsg)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::msg::proto::_PackageMsg_default_instance_._instance,
};

const char descriptor_table_protodef_package_5fmsg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021package_msg.proto\022\tmsg.proto\"\177\n\nPackag"
  "eMsg\022\013\n\003ack\030\001 \002(\004\022\r\n\005order\030\002 \002(\r\022\017\n\007data"
  "Len\030\003 \002(\r\022\021\n\ttatolSzie\030\004 \002(\r\022#\n\007msgType\030"
  "\005 \002(\0162\022.msg.proto.MsgType\022\014\n\004data\030\006 \002(\014*"
  "P\n\007MsgType\022\013\n\007Command\020\001\022\r\n\tFileInfos\020\002\022\024"
  "\n\020FileDownloadInfo\020\003\022\023\n\017FileDownloadRes\020"
  "\004B\002H\002"
  ;
static ::_pbi::once_flag descriptor_table_package_5fmsg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_package_5fmsg_2eproto = {
    false, false, 245, descriptor_table_protodef_package_5fmsg_2eproto,
    "package_msg.proto",
    &descriptor_table_package_5fmsg_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_package_5fmsg_2eproto::offsets,
    file_level_metadata_package_5fmsg_2eproto, file_level_enum_descriptors_package_5fmsg_2eproto,
    file_level_service_descriptors_package_5fmsg_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_package_5fmsg_2eproto_getter() {
  return &descriptor_table_package_5fmsg_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_package_5fmsg_2eproto(&descriptor_table_package_5fmsg_2eproto);
namespace msg {
namespace proto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MsgType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_package_5fmsg_2eproto);
  return file_level_enum_descriptors_package_5fmsg_2eproto[0];
}
bool MsgType_IsValid(int value) {
  switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class PackageMsg::_Internal {
 public:
  using HasBits = decltype(std::declval<PackageMsg>()._impl_._has_bits_);
  static void set_has_ack(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_order(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_datalen(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_tatolszie(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static void set_has_msgtype(HasBits* has_bits) {
    (*has_bits)[0] |= 32u;
  }
  static void set_has_data(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x0000003f) ^ 0x0000003f) != 0;
  }
};

PackageMsg::PackageMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:msg.proto.PackageMsg)
}
PackageMsg::PackageMsg(const PackageMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PackageMsg* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.data_){}
    , decltype(_impl_.ack_){}
    , decltype(_impl_.order_){}
    , decltype(_impl_.datalen_){}
    , decltype(_impl_.tatolszie_){}
    , decltype(_impl_.msgtype_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_data()) {
    _this->_impl_.data_.Set(from._internal_data(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.ack_, &from._impl_.ack_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.msgtype_) -
    reinterpret_cast<char*>(&_impl_.ack_)) + sizeof(_impl_.msgtype_));
  // @@protoc_insertion_point(copy_constructor:msg.proto.PackageMsg)
}

inline void PackageMsg::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.data_){}
    , decltype(_impl_.ack_){uint64_t{0u}}
    , decltype(_impl_.order_){0u}
    , decltype(_impl_.datalen_){0u}
    , decltype(_impl_.tatolszie_){0u}
    , decltype(_impl_.msgtype_){1}
  };
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PackageMsg::~PackageMsg() {
  // @@protoc_insertion_point(destructor:msg.proto.PackageMsg)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PackageMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.data_.Destroy();
}

void PackageMsg::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PackageMsg::InternalSwap(PackageMsg* other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::PROTOBUF_NAMESPACE_ID::Metadata PackageMsg::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_package_5fmsg_2eproto_getter, &descriptor_table_package_5fmsg_2eproto_once,
      file_level_metadata_package_5fmsg_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace msg
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::msg::proto::PackageMsg*
Arena::CreateMaybeMessage< ::msg::proto::PackageMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::msg::proto::PackageMsg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>