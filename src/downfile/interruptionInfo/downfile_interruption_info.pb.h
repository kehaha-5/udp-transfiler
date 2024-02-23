// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: downfile_interruption_info.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_downfile_5finterruption_5finfo_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_downfile_5finterruption_5finfo_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_downfile_5finterruption_5finfo_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_downfile_5finterruption_5finfo_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_downfile_5finterruption_5finfo_2eproto;
namespace downfile {
namespace interruption {
class DownfileInterruptionInfo;
struct DownfileInterruptionInfoDefaultTypeInternal;
extern DownfileInterruptionInfoDefaultTypeInternal _DownfileInterruptionInfo_default_instance_;
class SingleBlockInfo;
struct SingleBlockInfoDefaultTypeInternal;
extern SingleBlockInfoDefaultTypeInternal _SingleBlockInfo_default_instance_;
}  // namespace interruption
}  // namespace downfile
PROTOBUF_NAMESPACE_OPEN
template<> ::downfile::interruption::DownfileInterruptionInfo* Arena::CreateMaybeMessage<::downfile::interruption::DownfileInterruptionInfo>(Arena*);
template<> ::downfile::interruption::SingleBlockInfo* Arena::CreateMaybeMessage<::downfile::interruption::SingleBlockInfo>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace downfile {
namespace interruption {

// ===================================================================

class SingleBlockInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:downfile.interruption.SingleBlockInfo) */ {
 public:
  inline SingleBlockInfo() : SingleBlockInfo(nullptr) {}
  ~SingleBlockInfo() override;
  explicit PROTOBUF_CONSTEXPR SingleBlockInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SingleBlockInfo(const SingleBlockInfo& from);
  SingleBlockInfo(SingleBlockInfo&& from) noexcept
    : SingleBlockInfo() {
    *this = ::std::move(from);
  }

  inline SingleBlockInfo& operator=(const SingleBlockInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline SingleBlockInfo& operator=(SingleBlockInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SingleBlockInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const SingleBlockInfo* internal_default_instance() {
    return reinterpret_cast<const SingleBlockInfo*>(
               &_SingleBlockInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SingleBlockInfo& a, SingleBlockInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(SingleBlockInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SingleBlockInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SingleBlockInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SingleBlockInfo>(arena);
  }
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SingleBlockInfo* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "downfile.interruption.SingleBlockInfo";
  }
  protected:
  explicit SingleBlockInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kStartPosFieldNumber = 1,
    kIsDownloadFieldNumber = 2,
  };
  // required uint64 startPos = 1;
  bool has_startpos() const;
  private:
  bool _internal_has_startpos() const;
  public:
  void clear_startpos();
  uint64_t startpos() const;
  void set_startpos(uint64_t value);
  private:
  uint64_t _internal_startpos() const;
  void _internal_set_startpos(uint64_t value);
  public:

  // required bool isDownload = 2 [default = false];
  bool has_isdownload() const;
  private:
  bool _internal_has_isdownload() const;
  public:
  void clear_isdownload();
  bool isdownload() const;
  void set_isdownload(bool value);
  private:
  bool _internal_isdownload() const;
  void _internal_set_isdownload(bool value);
  public:

  // @@protoc_insertion_point(class_scope:downfile.interruption.SingleBlockInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    uint64_t startpos_;
    bool isdownload_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_downfile_5finterruption_5finfo_2eproto;
};
// -------------------------------------------------------------------

class DownfileInterruptionInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:downfile.interruption.DownfileInterruptionInfo) */ {
 public:
  inline DownfileInterruptionInfo() : DownfileInterruptionInfo(nullptr) {}
  ~DownfileInterruptionInfo() override;
  explicit PROTOBUF_CONSTEXPR DownfileInterruptionInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  DownfileInterruptionInfo(const DownfileInterruptionInfo& from);
  DownfileInterruptionInfo(DownfileInterruptionInfo&& from) noexcept
    : DownfileInterruptionInfo() {
    *this = ::std::move(from);
  }

  inline DownfileInterruptionInfo& operator=(const DownfileInterruptionInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline DownfileInterruptionInfo& operator=(DownfileInterruptionInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const DownfileInterruptionInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const DownfileInterruptionInfo* internal_default_instance() {
    return reinterpret_cast<const DownfileInterruptionInfo*>(
               &_DownfileInterruptionInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(DownfileInterruptionInfo& a, DownfileInterruptionInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(DownfileInterruptionInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(DownfileInterruptionInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  DownfileInterruptionInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<DownfileInterruptionInfo>(arena);
  }
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DownfileInterruptionInfo* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "downfile.interruption.DownfileInterruptionInfo";
  }
  protected:
  explicit DownfileInterruptionInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kInfoFieldNumber = 1,
    kNameFieldNumber = 2,
    kHashFieldNumber = 3,
    kHasDownloadedSizeFieldNumber = 4,
    kTotalSizeFieldNumber = 5,
    kIsfinishFieldNumber = 6,
  };
  // repeated .downfile.interruption.SingleBlockInfo info = 1;
  int info_size() const;
  private:
  int _internal_info_size() const;
  public:
  void clear_info();
  ::downfile::interruption::SingleBlockInfo* mutable_info(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::downfile::interruption::SingleBlockInfo >*
      mutable_info();
  private:
  const ::downfile::interruption::SingleBlockInfo& _internal_info(int index) const;
  ::downfile::interruption::SingleBlockInfo* _internal_add_info();
  public:
  const ::downfile::interruption::SingleBlockInfo& info(int index) const;
  ::downfile::interruption::SingleBlockInfo* add_info();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::downfile::interruption::SingleBlockInfo >&
      info() const;

  // required bytes name = 2;
  bool has_name() const;
  private:
  bool _internal_has_name() const;
  public:
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // required bytes hash = 3;
  bool has_hash() const;
  private:
  bool _internal_has_hash() const;
  public:
  void clear_hash();
  const std::string& hash() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_hash(ArgT0&& arg0, ArgT... args);
  std::string* mutable_hash();
  PROTOBUF_NODISCARD std::string* release_hash();
  void set_allocated_hash(std::string* hash);
  private:
  const std::string& _internal_hash() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_hash(const std::string& value);
  std::string* _internal_mutable_hash();
  public:

  // required uint64 hasDownloadedSize = 4 [default = 0];
  bool has_hasdownloadedsize() const;
  private:
  bool _internal_has_hasdownloadedsize() const;
  public:
  void clear_hasdownloadedsize();
  uint64_t hasdownloadedsize() const;
  void set_hasdownloadedsize(uint64_t value);
  private:
  uint64_t _internal_hasdownloadedsize() const;
  void _internal_set_hasdownloadedsize(uint64_t value);
  public:

  // required uint64 totalSize = 5 [default = 0];
  bool has_totalsize() const;
  private:
  bool _internal_has_totalsize() const;
  public:
  void clear_totalsize();
  uint64_t totalsize() const;
  void set_totalsize(uint64_t value);
  private:
  uint64_t _internal_totalsize() const;
  void _internal_set_totalsize(uint64_t value);
  public:

  // required bool isfinish = 6 [default = false];
  bool has_isfinish() const;
  private:
  bool _internal_has_isfinish() const;
  public:
  void clear_isfinish();
  bool isfinish() const;
  void set_isfinish(bool value);
  private:
  bool _internal_isfinish() const;
  void _internal_set_isfinish(bool value);
  public:

  // @@protoc_insertion_point(class_scope:downfile.interruption.DownfileInterruptionInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::downfile::interruption::SingleBlockInfo > info_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr hash_;
    uint64_t hasdownloadedsize_;
    uint64_t totalsize_;
    bool isfinish_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_downfile_5finterruption_5finfo_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SingleBlockInfo

// required uint64 startPos = 1;
inline bool SingleBlockInfo::_internal_has_startpos() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool SingleBlockInfo::has_startpos() const {
  return _internal_has_startpos();
}
inline void SingleBlockInfo::clear_startpos() {
  _impl_.startpos_ = uint64_t{0u};
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline uint64_t SingleBlockInfo::_internal_startpos() const {
  return _impl_.startpos_;
}
inline uint64_t SingleBlockInfo::startpos() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.SingleBlockInfo.startPos)
  return _internal_startpos();
}
inline void SingleBlockInfo::_internal_set_startpos(uint64_t value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.startpos_ = value;
}
inline void SingleBlockInfo::set_startpos(uint64_t value) {
  _internal_set_startpos(value);
  // @@protoc_insertion_point(field_set:downfile.interruption.SingleBlockInfo.startPos)
}

// required bool isDownload = 2 [default = false];
inline bool SingleBlockInfo::_internal_has_isdownload() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool SingleBlockInfo::has_isdownload() const {
  return _internal_has_isdownload();
}
inline void SingleBlockInfo::clear_isdownload() {
  _impl_.isdownload_ = false;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline bool SingleBlockInfo::_internal_isdownload() const {
  return _impl_.isdownload_;
}
inline bool SingleBlockInfo::isdownload() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.SingleBlockInfo.isDownload)
  return _internal_isdownload();
}
inline void SingleBlockInfo::_internal_set_isdownload(bool value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.isdownload_ = value;
}
inline void SingleBlockInfo::set_isdownload(bool value) {
  _internal_set_isdownload(value);
  // @@protoc_insertion_point(field_set:downfile.interruption.SingleBlockInfo.isDownload)
}

// -------------------------------------------------------------------

// DownfileInterruptionInfo

// repeated .downfile.interruption.SingleBlockInfo info = 1;
inline int DownfileInterruptionInfo::_internal_info_size() const {
  return _impl_.info_.size();
}
inline int DownfileInterruptionInfo::info_size() const {
  return _internal_info_size();
}
inline void DownfileInterruptionInfo::clear_info() {
  _impl_.info_.Clear();
}
inline ::downfile::interruption::SingleBlockInfo* DownfileInterruptionInfo::mutable_info(int index) {
  // @@protoc_insertion_point(field_mutable:downfile.interruption.DownfileInterruptionInfo.info)
  return _impl_.info_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::downfile::interruption::SingleBlockInfo >*
DownfileInterruptionInfo::mutable_info() {
  // @@protoc_insertion_point(field_mutable_list:downfile.interruption.DownfileInterruptionInfo.info)
  return &_impl_.info_;
}
inline const ::downfile::interruption::SingleBlockInfo& DownfileInterruptionInfo::_internal_info(int index) const {
  return _impl_.info_.Get(index);
}
inline const ::downfile::interruption::SingleBlockInfo& DownfileInterruptionInfo::info(int index) const {
  // @@protoc_insertion_point(field_get:downfile.interruption.DownfileInterruptionInfo.info)
  return _internal_info(index);
}
inline ::downfile::interruption::SingleBlockInfo* DownfileInterruptionInfo::_internal_add_info() {
  return _impl_.info_.Add();
}
inline ::downfile::interruption::SingleBlockInfo* DownfileInterruptionInfo::add_info() {
  ::downfile::interruption::SingleBlockInfo* _add = _internal_add_info();
  // @@protoc_insertion_point(field_add:downfile.interruption.DownfileInterruptionInfo.info)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::downfile::interruption::SingleBlockInfo >&
DownfileInterruptionInfo::info() const {
  // @@protoc_insertion_point(field_list:downfile.interruption.DownfileInterruptionInfo.info)
  return _impl_.info_;
}

// required bytes name = 2;
inline bool DownfileInterruptionInfo::_internal_has_name() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool DownfileInterruptionInfo::has_name() const {
  return _internal_has_name();
}
inline void DownfileInterruptionInfo::clear_name() {
  _impl_.name_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& DownfileInterruptionInfo::name() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.DownfileInterruptionInfo.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void DownfileInterruptionInfo::set_name(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000001u;
 _impl_.name_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:downfile.interruption.DownfileInterruptionInfo.name)
}
inline std::string* DownfileInterruptionInfo::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:downfile.interruption.DownfileInterruptionInfo.name)
  return _s;
}
inline const std::string& DownfileInterruptionInfo::_internal_name() const {
  return _impl_.name_.Get();
}
inline void DownfileInterruptionInfo::_internal_set_name(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* DownfileInterruptionInfo::_internal_mutable_name() {
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* DownfileInterruptionInfo::release_name() {
  // @@protoc_insertion_point(field_release:downfile.interruption.DownfileInterruptionInfo.name)
  if (!_internal_has_name()) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* p = _impl_.name_.Release();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return p;
}
inline void DownfileInterruptionInfo::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.name_.SetAllocated(name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:downfile.interruption.DownfileInterruptionInfo.name)
}

// required bytes hash = 3;
inline bool DownfileInterruptionInfo::_internal_has_hash() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool DownfileInterruptionInfo::has_hash() const {
  return _internal_has_hash();
}
inline void DownfileInterruptionInfo::clear_hash() {
  _impl_.hash_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& DownfileInterruptionInfo::hash() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.DownfileInterruptionInfo.hash)
  return _internal_hash();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void DownfileInterruptionInfo::set_hash(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000002u;
 _impl_.hash_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:downfile.interruption.DownfileInterruptionInfo.hash)
}
inline std::string* DownfileInterruptionInfo::mutable_hash() {
  std::string* _s = _internal_mutable_hash();
  // @@protoc_insertion_point(field_mutable:downfile.interruption.DownfileInterruptionInfo.hash)
  return _s;
}
inline const std::string& DownfileInterruptionInfo::_internal_hash() const {
  return _impl_.hash_.Get();
}
inline void DownfileInterruptionInfo::_internal_set_hash(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.hash_.Set(value, GetArenaForAllocation());
}
inline std::string* DownfileInterruptionInfo::_internal_mutable_hash() {
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.hash_.Mutable(GetArenaForAllocation());
}
inline std::string* DownfileInterruptionInfo::release_hash() {
  // @@protoc_insertion_point(field_release:downfile.interruption.DownfileInterruptionInfo.hash)
  if (!_internal_has_hash()) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000002u;
  auto* p = _impl_.hash_.Release();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.hash_.IsDefault()) {
    _impl_.hash_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return p;
}
inline void DownfileInterruptionInfo::set_allocated_hash(std::string* hash) {
  if (hash != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  _impl_.hash_.SetAllocated(hash, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.hash_.IsDefault()) {
    _impl_.hash_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:downfile.interruption.DownfileInterruptionInfo.hash)
}

// required uint64 hasDownloadedSize = 4 [default = 0];
inline bool DownfileInterruptionInfo::_internal_has_hasdownloadedsize() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool DownfileInterruptionInfo::has_hasdownloadedsize() const {
  return _internal_has_hasdownloadedsize();
}
inline void DownfileInterruptionInfo::clear_hasdownloadedsize() {
  _impl_.hasdownloadedsize_ = uint64_t{0u};
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline uint64_t DownfileInterruptionInfo::_internal_hasdownloadedsize() const {
  return _impl_.hasdownloadedsize_;
}
inline uint64_t DownfileInterruptionInfo::hasdownloadedsize() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.DownfileInterruptionInfo.hasDownloadedSize)
  return _internal_hasdownloadedsize();
}
inline void DownfileInterruptionInfo::_internal_set_hasdownloadedsize(uint64_t value) {
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.hasdownloadedsize_ = value;
}
inline void DownfileInterruptionInfo::set_hasdownloadedsize(uint64_t value) {
  _internal_set_hasdownloadedsize(value);
  // @@protoc_insertion_point(field_set:downfile.interruption.DownfileInterruptionInfo.hasDownloadedSize)
}

// required uint64 totalSize = 5 [default = 0];
inline bool DownfileInterruptionInfo::_internal_has_totalsize() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool DownfileInterruptionInfo::has_totalsize() const {
  return _internal_has_totalsize();
}
inline void DownfileInterruptionInfo::clear_totalsize() {
  _impl_.totalsize_ = uint64_t{0u};
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline uint64_t DownfileInterruptionInfo::_internal_totalsize() const {
  return _impl_.totalsize_;
}
inline uint64_t DownfileInterruptionInfo::totalsize() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.DownfileInterruptionInfo.totalSize)
  return _internal_totalsize();
}
inline void DownfileInterruptionInfo::_internal_set_totalsize(uint64_t value) {
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.totalsize_ = value;
}
inline void DownfileInterruptionInfo::set_totalsize(uint64_t value) {
  _internal_set_totalsize(value);
  // @@protoc_insertion_point(field_set:downfile.interruption.DownfileInterruptionInfo.totalSize)
}

// required bool isfinish = 6 [default = false];
inline bool DownfileInterruptionInfo::_internal_has_isfinish() const {
  bool value = (_impl_._has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool DownfileInterruptionInfo::has_isfinish() const {
  return _internal_has_isfinish();
}
inline void DownfileInterruptionInfo::clear_isfinish() {
  _impl_.isfinish_ = false;
  _impl_._has_bits_[0] &= ~0x00000010u;
}
inline bool DownfileInterruptionInfo::_internal_isfinish() const {
  return _impl_.isfinish_;
}
inline bool DownfileInterruptionInfo::isfinish() const {
  // @@protoc_insertion_point(field_get:downfile.interruption.DownfileInterruptionInfo.isfinish)
  return _internal_isfinish();
}
inline void DownfileInterruptionInfo::_internal_set_isfinish(bool value) {
  _impl_._has_bits_[0] |= 0x00000010u;
  _impl_.isfinish_ = value;
}
inline void DownfileInterruptionInfo::set_isfinish(bool value) {
  _internal_set_isfinish(value);
  // @@protoc_insertion_point(field_set:downfile.interruption.DownfileInterruptionInfo.isfinish)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace interruption
}  // namespace downfile

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_downfile_5finterruption_5finfo_2eproto
