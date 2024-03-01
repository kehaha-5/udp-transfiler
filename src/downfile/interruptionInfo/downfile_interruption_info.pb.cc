// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: downfile_interruption_info.proto

#include "downfile_interruption_info.pb.h"

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

namespace downfile {
namespace interruption {
PROTOBUF_CONSTEXPR SingleBlockInfo::SingleBlockInfo(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.posindex_)*/uint64_t{0u}
  , /*decltype(_impl_.isdownload_)*/false} {}
struct SingleBlockInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SingleBlockInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SingleBlockInfoDefaultTypeInternal() {}
  union {
    SingleBlockInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SingleBlockInfoDefaultTypeInternal _SingleBlockInfo_default_instance_;
PROTOBUF_CONSTEXPR DownfileInterruptionInfo::DownfileInterruptionInfo(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.info_)*/{}
  , /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.hash_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.hasdownloadedsize_)*/uint64_t{0u}
  , /*decltype(_impl_.totalsize_)*/uint64_t{0u}
  , /*decltype(_impl_.isfinish_)*/false} {}
struct DownfileInterruptionInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR DownfileInterruptionInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~DownfileInterruptionInfoDefaultTypeInternal() {}
  union {
    DownfileInterruptionInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 DownfileInterruptionInfoDefaultTypeInternal _DownfileInterruptionInfo_default_instance_;
}  // namespace interruption
}  // namespace downfile
static ::_pb::Metadata file_level_metadata_downfile_5finterruption_5finfo_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_downfile_5finterruption_5finfo_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_downfile_5finterruption_5finfo_2eproto = nullptr;

const uint32_t TableStruct_downfile_5finterruption_5finfo_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::SingleBlockInfo, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::SingleBlockInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::SingleBlockInfo, _impl_.posindex_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::SingleBlockInfo, _impl_.isdownload_),
  0,
  1,
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_.info_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_.hash_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_.hasdownloadedsize_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_.totalsize_),
  PROTOBUF_FIELD_OFFSET(::downfile::interruption::DownfileInterruptionInfo, _impl_.isfinish_),
  ~0u,
  0,
  1,
  2,
  3,
  4,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, -1, sizeof(::downfile::interruption::SingleBlockInfo)},
  { 10, 22, -1, sizeof(::downfile::interruption::DownfileInterruptionInfo)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::downfile::interruption::_SingleBlockInfo_default_instance_._instance,
  &::downfile::interruption::_DownfileInterruptionInfo_default_instance_._instance,
};

const char descriptor_table_protodef_downfile_5finterruption_5finfo_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n downfile_interruption_info.proto\022\025down"
  "file.interruption\">\n\017SingleBlockInfo\022\020\n\010"
  "posIndex\030\001 \002(\004\022\031\n\nisdownload\030\002 \002(\010:\005fals"
  "e\"\271\001\n\030DownfileInterruptionInfo\0224\n\004info\030\001"
  " \003(\0132&.downfile.interruption.SingleBlock"
  "Info\022\014\n\004name\030\002 \002(\014\022\014\n\004hash\030\003 \002(\014\022\034\n\021hasD"
  "ownloadedSize\030\004 \002(\004:\0010\022\024\n\ttotalSize\030\005 \002("
  "\004:\0010\022\027\n\010isfinish\030\006 \002(\010:\005false"
  ;
static ::_pbi::once_flag descriptor_table_downfile_5finterruption_5finfo_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_downfile_5finterruption_5finfo_2eproto = {
    false, false, 309, descriptor_table_protodef_downfile_5finterruption_5finfo_2eproto,
    "downfile_interruption_info.proto",
    &descriptor_table_downfile_5finterruption_5finfo_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_downfile_5finterruption_5finfo_2eproto::offsets,
    file_level_metadata_downfile_5finterruption_5finfo_2eproto, file_level_enum_descriptors_downfile_5finterruption_5finfo_2eproto,
    file_level_service_descriptors_downfile_5finterruption_5finfo_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_downfile_5finterruption_5finfo_2eproto_getter() {
  return &descriptor_table_downfile_5finterruption_5finfo_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_downfile_5finterruption_5finfo_2eproto(&descriptor_table_downfile_5finterruption_5finfo_2eproto);
namespace downfile {
namespace interruption {

// ===================================================================

class SingleBlockInfo::_Internal {
 public:
  using HasBits = decltype(std::declval<SingleBlockInfo>()._impl_._has_bits_);
  static void set_has_posindex(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_isdownload(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000003) ^ 0x00000003) != 0;
  }
};

SingleBlockInfo::SingleBlockInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:downfile.interruption.SingleBlockInfo)
}
SingleBlockInfo::SingleBlockInfo(const SingleBlockInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SingleBlockInfo* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.posindex_){}
    , decltype(_impl_.isdownload_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.posindex_, &from._impl_.posindex_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.isdownload_) -
    reinterpret_cast<char*>(&_impl_.posindex_)) + sizeof(_impl_.isdownload_));
  // @@protoc_insertion_point(copy_constructor:downfile.interruption.SingleBlockInfo)
}

inline void SingleBlockInfo::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.posindex_){uint64_t{0u}}
    , decltype(_impl_.isdownload_){false}
  };
}

SingleBlockInfo::~SingleBlockInfo() {
  // @@protoc_insertion_point(destructor:downfile.interruption.SingleBlockInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SingleBlockInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void SingleBlockInfo::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SingleBlockInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:downfile.interruption.SingleBlockInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&_impl_.posindex_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&_impl_.isdownload_) -
        reinterpret_cast<char*>(&_impl_.posindex_)) + sizeof(_impl_.isdownload_));
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SingleBlockInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // required uint64 posIndex = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_posindex(&has_bits);
          _impl_.posindex_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required bool isdownload = 2 [default = false];
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _Internal::set_has_isdownload(&has_bits);
          _impl_.isdownload_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
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

uint8_t* SingleBlockInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:downfile.interruption.SingleBlockInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // required uint64 posIndex = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_posindex(), target);
  }

  // required bool isdownload = 2 [default = false];
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(2, this->_internal_isdownload(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:downfile.interruption.SingleBlockInfo)
  return target;
}

size_t SingleBlockInfo::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:downfile.interruption.SingleBlockInfo)
  size_t total_size = 0;

  if (_internal_has_posindex()) {
    // required uint64 posIndex = 1;
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_posindex());
  }

  if (_internal_has_isdownload()) {
    // required bool isdownload = 2 [default = false];
    total_size += 1 + 1;
  }

  return total_size;
}
size_t SingleBlockInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:downfile.interruption.SingleBlockInfo)
  size_t total_size = 0;

  if (((_impl_._has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required uint64 posIndex = 1;
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_posindex());

    // required bool isdownload = 2 [default = false];
    total_size += 1 + 1;

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SingleBlockInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SingleBlockInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SingleBlockInfo::GetClassData() const { return &_class_data_; }


void SingleBlockInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SingleBlockInfo*>(&to_msg);
  auto& from = static_cast<const SingleBlockInfo&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:downfile.interruption.SingleBlockInfo)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _this->_impl_.posindex_ = from._impl_.posindex_;
    }
    if (cached_has_bits & 0x00000002u) {
      _this->_impl_.isdownload_ = from._impl_.isdownload_;
    }
    _this->_impl_._has_bits_[0] |= cached_has_bits;
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SingleBlockInfo::CopyFrom(const SingleBlockInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:downfile.interruption.SingleBlockInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SingleBlockInfo::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_impl_._has_bits_)) return false;
  return true;
}

void SingleBlockInfo::InternalSwap(SingleBlockInfo* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(SingleBlockInfo, _impl_.isdownload_)
      + sizeof(SingleBlockInfo::_impl_.isdownload_)
      - PROTOBUF_FIELD_OFFSET(SingleBlockInfo, _impl_.posindex_)>(
          reinterpret_cast<char*>(&_impl_.posindex_),
          reinterpret_cast<char*>(&other->_impl_.posindex_));
}

::PROTOBUF_NAMESPACE_ID::Metadata SingleBlockInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_downfile_5finterruption_5finfo_2eproto_getter, &descriptor_table_downfile_5finterruption_5finfo_2eproto_once,
      file_level_metadata_downfile_5finterruption_5finfo_2eproto[0]);
}

// ===================================================================

class DownfileInterruptionInfo::_Internal {
 public:
  using HasBits = decltype(std::declval<DownfileInterruptionInfo>()._impl_._has_bits_);
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_hash(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_hasdownloadedsize(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_totalsize(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_isfinish(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x0000001f) ^ 0x0000001f) != 0;
  }
};

DownfileInterruptionInfo::DownfileInterruptionInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:downfile.interruption.DownfileInterruptionInfo)
}
DownfileInterruptionInfo::DownfileInterruptionInfo(const DownfileInterruptionInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  DownfileInterruptionInfo* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.info_){from._impl_.info_}
    , decltype(_impl_.name_){}
    , decltype(_impl_.hash_){}
    , decltype(_impl_.hasdownloadedsize_){}
    , decltype(_impl_.totalsize_){}
    , decltype(_impl_.isfinish_){}};

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
  ::memcpy(&_impl_.hasdownloadedsize_, &from._impl_.hasdownloadedsize_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.isfinish_) -
    reinterpret_cast<char*>(&_impl_.hasdownloadedsize_)) + sizeof(_impl_.isfinish_));
  // @@protoc_insertion_point(copy_constructor:downfile.interruption.DownfileInterruptionInfo)
}

inline void DownfileInterruptionInfo::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.info_){arena}
    , decltype(_impl_.name_){}
    , decltype(_impl_.hash_){}
    , decltype(_impl_.hasdownloadedsize_){uint64_t{0u}}
    , decltype(_impl_.totalsize_){uint64_t{0u}}
    , decltype(_impl_.isfinish_){false}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.hash_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.hash_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

DownfileInterruptionInfo::~DownfileInterruptionInfo() {
  // @@protoc_insertion_point(destructor:downfile.interruption.DownfileInterruptionInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void DownfileInterruptionInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.info_.~RepeatedPtrField();
  _impl_.name_.Destroy();
  _impl_.hash_.Destroy();
}

void DownfileInterruptionInfo::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void DownfileInterruptionInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:downfile.interruption.DownfileInterruptionInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.info_.Clear();
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _impl_.name_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      _impl_.hash_.ClearNonDefaultToEmpty();
    }
  }
  if (cached_has_bits & 0x0000001cu) {
    ::memset(&_impl_.hasdownloadedsize_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&_impl_.isfinish_) -
        reinterpret_cast<char*>(&_impl_.hasdownloadedsize_)) + sizeof(_impl_.isfinish_));
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* DownfileInterruptionInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .downfile.interruption.SingleBlockInfo info = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_info(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      // required bytes name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required bytes hash = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_hash();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required uint64 hasDownloadedSize = 4 [default = 0];
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _Internal::set_has_hasdownloadedsize(&has_bits);
          _impl_.hasdownloadedsize_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required uint64 totalSize = 5 [default = 0];
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _Internal::set_has_totalsize(&has_bits);
          _impl_.totalsize_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required bool isfinish = 6 [default = false];
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _Internal::set_has_isfinish(&has_bits);
          _impl_.isfinish_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
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

uint8_t* DownfileInterruptionInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:downfile.interruption.DownfileInterruptionInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .downfile.interruption.SingleBlockInfo info = 1;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_info_size()); i < n; i++) {
    const auto& repfield = this->_internal_info(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(1, repfield, repfield.GetCachedSize(), target, stream);
  }

  cached_has_bits = _impl_._has_bits_[0];
  // required bytes name = 2;
  if (cached_has_bits & 0x00000001u) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_name(), target);
  }

  // required bytes hash = 3;
  if (cached_has_bits & 0x00000002u) {
    target = stream->WriteBytesMaybeAliased(
        3, this->_internal_hash(), target);
  }

  // required uint64 hasDownloadedSize = 4 [default = 0];
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(4, this->_internal_hasdownloadedsize(), target);
  }

  // required uint64 totalSize = 5 [default = 0];
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(5, this->_internal_totalsize(), target);
  }

  // required bool isfinish = 6 [default = false];
  if (cached_has_bits & 0x00000010u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(6, this->_internal_isfinish(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:downfile.interruption.DownfileInterruptionInfo)
  return target;
}

size_t DownfileInterruptionInfo::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:downfile.interruption.DownfileInterruptionInfo)
  size_t total_size = 0;

  if (_internal_has_name()) {
    // required bytes name = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_name());
  }

  if (_internal_has_hash()) {
    // required bytes hash = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_hash());
  }

  if (_internal_has_hasdownloadedsize()) {
    // required uint64 hasDownloadedSize = 4 [default = 0];
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_hasdownloadedsize());
  }

  if (_internal_has_totalsize()) {
    // required uint64 totalSize = 5 [default = 0];
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_totalsize());
  }

  if (_internal_has_isfinish()) {
    // required bool isfinish = 6 [default = false];
    total_size += 1 + 1;
  }

  return total_size;
}
size_t DownfileInterruptionInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:downfile.interruption.DownfileInterruptionInfo)
  size_t total_size = 0;

  if (((_impl_._has_bits_[0] & 0x0000001f) ^ 0x0000001f) == 0) {  // All required fields are present.
    // required bytes name = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_name());

    // required bytes hash = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_hash());

    // required uint64 hasDownloadedSize = 4 [default = 0];
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_hasdownloadedsize());

    // required uint64 totalSize = 5 [default = 0];
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_totalsize());

    // required bool isfinish = 6 [default = false];
    total_size += 1 + 1;

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .downfile.interruption.SingleBlockInfo info = 1;
  total_size += 1UL * this->_internal_info_size();
  for (const auto& msg : this->_impl_.info_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData DownfileInterruptionInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    DownfileInterruptionInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*DownfileInterruptionInfo::GetClassData() const { return &_class_data_; }


void DownfileInterruptionInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<DownfileInterruptionInfo*>(&to_msg);
  auto& from = static_cast<const DownfileInterruptionInfo&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:downfile.interruption.DownfileInterruptionInfo)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.info_.MergeFrom(from._impl_.info_);
  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _this->_internal_set_name(from._internal_name());
    }
    if (cached_has_bits & 0x00000002u) {
      _this->_internal_set_hash(from._internal_hash());
    }
    if (cached_has_bits & 0x00000004u) {
      _this->_impl_.hasdownloadedsize_ = from._impl_.hasdownloadedsize_;
    }
    if (cached_has_bits & 0x00000008u) {
      _this->_impl_.totalsize_ = from._impl_.totalsize_;
    }
    if (cached_has_bits & 0x00000010u) {
      _this->_impl_.isfinish_ = from._impl_.isfinish_;
    }
    _this->_impl_._has_bits_[0] |= cached_has_bits;
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void DownfileInterruptionInfo::CopyFrom(const DownfileInterruptionInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:downfile.interruption.DownfileInterruptionInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DownfileInterruptionInfo::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_impl_._has_bits_)) return false;
  if (!::PROTOBUF_NAMESPACE_ID::internal::AllAreInitialized(_impl_.info_))
    return false;
  return true;
}

void DownfileInterruptionInfo::InternalSwap(DownfileInterruptionInfo* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  _impl_.info_.InternalSwap(&other->_impl_.info_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.hash_, lhs_arena,
      &other->_impl_.hash_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(DownfileInterruptionInfo, _impl_.isfinish_)
      + sizeof(DownfileInterruptionInfo::_impl_.isfinish_)
      - PROTOBUF_FIELD_OFFSET(DownfileInterruptionInfo, _impl_.hasdownloadedsize_)>(
          reinterpret_cast<char*>(&_impl_.hasdownloadedsize_),
          reinterpret_cast<char*>(&other->_impl_.hasdownloadedsize_));
}

::PROTOBUF_NAMESPACE_ID::Metadata DownfileInterruptionInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_downfile_5finterruption_5finfo_2eproto_getter, &descriptor_table_downfile_5finterruption_5finfo_2eproto_once,
      file_level_metadata_downfile_5finterruption_5finfo_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace interruption
}  // namespace downfile
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::downfile::interruption::SingleBlockInfo*
Arena::CreateMaybeMessage< ::downfile::interruption::SingleBlockInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::downfile::interruption::SingleBlockInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::downfile::interruption::DownfileInterruptionInfo*
Arena::CreateMaybeMessage< ::downfile::interruption::DownfileInterruptionInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::downfile::interruption::DownfileInterruptionInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
