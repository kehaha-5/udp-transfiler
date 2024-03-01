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
  "2\027.msg.proto.fileDownInfo"
  ;
static ::_pbi::once_flag descriptor_table_file_5fdown_5finfo_5fmsg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_file_5fdown_5finfo_5fmsg_2eproto = {
    false, false, 185, descriptor_table_protodef_file_5fdown_5finfo_5fmsg_2eproto,
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

void fileDownInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:msg.proto.fileDownInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _impl_.name_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      _impl_.hash_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000004u) {
      _impl_.humanreadablesize_.ClearNonDefaultToEmpty();
    }
  }
  _impl_.size_ = uint64_t{0u};
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* fileDownInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // required string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          #ifndef NDEBUG
          ::_pbi::VerifyUTF8(str, "msg.proto.fileDownInfo.name");
          #endif  // !NDEBUG
        } else
          goto handle_unusual;
        continue;
      // required uint64 size = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _Internal::set_has_size(&has_bits);
          _impl_.size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required string hash = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_hash();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          #ifndef NDEBUG
          ::_pbi::VerifyUTF8(str, "msg.proto.fileDownInfo.hash");
          #endif  // !NDEBUG
        } else
          goto handle_unusual;
        continue;
      // required string humanReadableSize = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_humanreadablesize();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          #ifndef NDEBUG
          ::_pbi::VerifyUTF8(str, "msg.proto.fileDownInfo.humanReadableSize");
          #endif  // !NDEBUG
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* fileDownInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg.proto.fileDownInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "msg.proto.fileDownInfo.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  // required uint64 size = 2;
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(2, this->_internal_size(), target);
  }

  // required string hash = 3;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_hash().data(), static_cast<int>(this->_internal_hash().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "msg.proto.fileDownInfo.hash");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_hash(), target);
  }

  // required string humanReadableSize = 4;
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_humanreadablesize().data(), static_cast<int>(this->_internal_humanreadablesize().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "msg.proto.fileDownInfo.humanReadableSize");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_humanreadablesize(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg.proto.fileDownInfo)
  return target;
}

size_t fileDownInfo::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:msg.proto.fileDownInfo)
  size_t total_size = 0;

  if (_internal_has_name()) {
    // required string name = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  if (_internal_has_hash()) {
    // required string hash = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_hash());
  }

  if (_internal_has_humanreadablesize()) {
    // required string humanReadableSize = 4;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_humanreadablesize());
  }

  if (_internal_has_size()) {
    // required uint64 size = 2;
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_size());
  }

  return total_size;
}
size_t fileDownInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:msg.proto.fileDownInfo)
  size_t total_size = 0;

  if (((_impl_._has_bits_[0] & 0x0000000f) ^ 0x0000000f) == 0) {  // All required fields are present.
    // required string name = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());

    // required string hash = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_hash());

    // required string humanReadableSize = 4;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_humanreadablesize());

    // required uint64 size = 2;
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_size());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData fileDownInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    fileDownInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*fileDownInfo::GetClassData() const { return &_class_data_; }


void fileDownInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<fileDownInfo*>(&to_msg);
  auto& from = static_cast<const fileDownInfo&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:msg.proto.fileDownInfo)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _this->_internal_set_name(from._internal_name());
    }
    if (cached_has_bits & 0x00000002u) {
      _this->_internal_set_hash(from._internal_hash());
    }
    if (cached_has_bits & 0x00000004u) {
      _this->_internal_set_humanreadablesize(from._internal_humanreadablesize());
    }
    if (cached_has_bits & 0x00000008u) {
      _this->_impl_.size_ = from._impl_.size_;
    }
    _this->_impl_._has_bits_[0] |= cached_has_bits;
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void fileDownInfo::CopyFrom(const fileDownInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:msg.proto.fileDownInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool fileDownInfo::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_impl_._has_bits_)) return false;
  return true;
}

void fileDownInfo::InternalSwap(fileDownInfo* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.hash_, lhs_arena,
      &other->_impl_.hash_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.humanreadablesize_, lhs_arena,
      &other->_impl_.humanreadablesize_, rhs_arena
  );
  swap(_impl_.size_, other->_impl_.size_);
}

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

void FileDownInfoMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:msg.proto.FileDownInfoMsg)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.fileinfos_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* FileDownInfoMsg::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .msg.proto.fileDownInfo fileinfos = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_fileinfos(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* FileDownInfoMsg::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg.proto.FileDownInfoMsg)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .msg.proto.fileDownInfo fileinfos = 1;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_fileinfos_size()); i < n; i++) {
    const auto& repfield = this->_internal_fileinfos(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(1, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg.proto.FileDownInfoMsg)
  return target;
}

size_t FileDownInfoMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:msg.proto.FileDownInfoMsg)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .msg.proto.fileDownInfo fileinfos = 1;
  total_size += 1UL * this->_internal_fileinfos_size();
  for (const auto& msg : this->_impl_.fileinfos_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData FileDownInfoMsg::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    FileDownInfoMsg::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*FileDownInfoMsg::GetClassData() const { return &_class_data_; }


void FileDownInfoMsg::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<FileDownInfoMsg*>(&to_msg);
  auto& from = static_cast<const FileDownInfoMsg&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:msg.proto.FileDownInfoMsg)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.fileinfos_.MergeFrom(from._impl_.fileinfos_);
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void FileDownInfoMsg::CopyFrom(const FileDownInfoMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:msg.proto.FileDownInfoMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FileDownInfoMsg::IsInitialized() const {
  if (!::PROTOBUF_NAMESPACE_ID::internal::AllAreInitialized(_impl_.fileinfos_))
    return false;
  return true;
}

void FileDownInfoMsg::InternalSwap(FileDownInfoMsg* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.fileinfos_.InternalSwap(&other->_impl_.fileinfos_);
}

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
