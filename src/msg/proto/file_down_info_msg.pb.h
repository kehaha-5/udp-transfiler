// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: file_down_info_msg.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_file_5fdown_5finfo_5fmsg_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_file_5fdown_5finfo_5fmsg_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_file_5fdown_5finfo_5fmsg_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_file_5fdown_5finfo_5fmsg_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_file_5fdown_5finfo_5fmsg_2eproto;
namespace msg {
namespace proto {
class FileDownInfoMsg;
struct FileDownInfoMsgDefaultTypeInternal;
extern FileDownInfoMsgDefaultTypeInternal _FileDownInfoMsg_default_instance_;
class fileDownInfo;
struct fileDownInfoDefaultTypeInternal;
extern fileDownInfoDefaultTypeInternal _fileDownInfo_default_instance_;
}  // namespace proto
}  // namespace msg
PROTOBUF_NAMESPACE_OPEN
template<> ::msg::proto::FileDownInfoMsg* Arena::CreateMaybeMessage<::msg::proto::FileDownInfoMsg>(Arena*);
template<> ::msg::proto::fileDownInfo* Arena::CreateMaybeMessage<::msg::proto::fileDownInfo>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace msg {
namespace proto {

// ===================================================================

class fileDownInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:msg.proto.fileDownInfo) */ {
 public:
  inline fileDownInfo() : fileDownInfo(nullptr) {}
  ~fileDownInfo() override;
  explicit PROTOBUF_CONSTEXPR fileDownInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  fileDownInfo(const fileDownInfo& from);
  fileDownInfo(fileDownInfo&& from) noexcept
    : fileDownInfo() {
    *this = ::std::move(from);
  }

  inline fileDownInfo& operator=(const fileDownInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline fileDownInfo& operator=(fileDownInfo&& from) noexcept {
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
  static const fileDownInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const fileDownInfo* internal_default_instance() {
    return reinterpret_cast<const fileDownInfo*>(
               &_fileDownInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(fileDownInfo& a, fileDownInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(fileDownInfo* other) {
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
  void UnsafeArenaSwap(fileDownInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  fileDownInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<fileDownInfo>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const fileDownInfo& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const fileDownInfo& from) {
    fileDownInfo::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(fileDownInfo* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "msg.proto.fileDownInfo";
  }
  protected:
  explicit fileDownInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
    kHashFieldNumber = 3,
    kHumanReadableSizeFieldNumber = 4,
    kSizeFieldNumber = 2,
  };
  // required string name = 1;
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

  // required string hash = 3;
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

  // required string humanReadableSize = 4;
  bool has_humanreadablesize() const;
  private:
  bool _internal_has_humanreadablesize() const;
  public:
  void clear_humanreadablesize();
  const std::string& humanreadablesize() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_humanreadablesize(ArgT0&& arg0, ArgT... args);
  std::string* mutable_humanreadablesize();
  PROTOBUF_NODISCARD std::string* release_humanreadablesize();
  void set_allocated_humanreadablesize(std::string* humanreadablesize);
  private:
  const std::string& _internal_humanreadablesize() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_humanreadablesize(const std::string& value);
  std::string* _internal_mutable_humanreadablesize();
  public:

  // required uint64 size = 2;
  bool has_size() const;
  private:
  bool _internal_has_size() const;
  public:
  void clear_size();
  uint64_t size() const;
  void set_size(uint64_t value);
  private:
  uint64_t _internal_size() const;
  void _internal_set_size(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:msg.proto.fileDownInfo)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr hash_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr humanreadablesize_;
    uint64_t size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_file_5fdown_5finfo_5fmsg_2eproto;
};
// -------------------------------------------------------------------

class FileDownInfoMsg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:msg.proto.FileDownInfoMsg) */ {
 public:
  inline FileDownInfoMsg() : FileDownInfoMsg(nullptr) {}
  ~FileDownInfoMsg() override;
  explicit PROTOBUF_CONSTEXPR FileDownInfoMsg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  FileDownInfoMsg(const FileDownInfoMsg& from);
  FileDownInfoMsg(FileDownInfoMsg&& from) noexcept
    : FileDownInfoMsg() {
    *this = ::std::move(from);
  }

  inline FileDownInfoMsg& operator=(const FileDownInfoMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline FileDownInfoMsg& operator=(FileDownInfoMsg&& from) noexcept {
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
  static const FileDownInfoMsg& default_instance() {
    return *internal_default_instance();
  }
  static inline const FileDownInfoMsg* internal_default_instance() {
    return reinterpret_cast<const FileDownInfoMsg*>(
               &_FileDownInfoMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(FileDownInfoMsg& a, FileDownInfoMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(FileDownInfoMsg* other) {
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
  void UnsafeArenaSwap(FileDownInfoMsg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  FileDownInfoMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<FileDownInfoMsg>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const FileDownInfoMsg& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const FileDownInfoMsg& from) {
    FileDownInfoMsg::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FileDownInfoMsg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "msg.proto.FileDownInfoMsg";
  }
  protected:
  explicit FileDownInfoMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFileinfosFieldNumber = 1,
  };
  // repeated .msg.proto.fileDownInfo fileinfos = 1;
  int fileinfos_size() const;
  private:
  int _internal_fileinfos_size() const;
  public:
  void clear_fileinfos();
  ::msg::proto::fileDownInfo* mutable_fileinfos(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::msg::proto::fileDownInfo >*
      mutable_fileinfos();
  private:
  const ::msg::proto::fileDownInfo& _internal_fileinfos(int index) const;
  ::msg::proto::fileDownInfo* _internal_add_fileinfos();
  public:
  const ::msg::proto::fileDownInfo& fileinfos(int index) const;
  ::msg::proto::fileDownInfo* add_fileinfos();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::msg::proto::fileDownInfo >&
      fileinfos() const;

  // @@protoc_insertion_point(class_scope:msg.proto.FileDownInfoMsg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::msg::proto::fileDownInfo > fileinfos_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_file_5fdown_5finfo_5fmsg_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// fileDownInfo

// required string name = 1;
inline bool fileDownInfo::_internal_has_name() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool fileDownInfo::has_name() const {
  return _internal_has_name();
}
inline void fileDownInfo::clear_name() {
  _impl_.name_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& fileDownInfo::name() const {
  // @@protoc_insertion_point(field_get:msg.proto.fileDownInfo.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void fileDownInfo::set_name(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000001u;
 _impl_.name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg.proto.fileDownInfo.name)
}
inline std::string* fileDownInfo::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:msg.proto.fileDownInfo.name)
  return _s;
}
inline const std::string& fileDownInfo::_internal_name() const {
  return _impl_.name_.Get();
}
inline void fileDownInfo::_internal_set_name(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* fileDownInfo::_internal_mutable_name() {
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* fileDownInfo::release_name() {
  // @@protoc_insertion_point(field_release:msg.proto.fileDownInfo.name)
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
inline void fileDownInfo::set_allocated_name(std::string* name) {
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
  // @@protoc_insertion_point(field_set_allocated:msg.proto.fileDownInfo.name)
}

// required uint64 size = 2;
inline bool fileDownInfo::_internal_has_size() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool fileDownInfo::has_size() const {
  return _internal_has_size();
}
inline void fileDownInfo::clear_size() {
  _impl_.size_ = uint64_t{0u};
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline uint64_t fileDownInfo::_internal_size() const {
  return _impl_.size_;
}
inline uint64_t fileDownInfo::size() const {
  // @@protoc_insertion_point(field_get:msg.proto.fileDownInfo.size)
  return _internal_size();
}
inline void fileDownInfo::_internal_set_size(uint64_t value) {
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.size_ = value;
}
inline void fileDownInfo::set_size(uint64_t value) {
  _internal_set_size(value);
  // @@protoc_insertion_point(field_set:msg.proto.fileDownInfo.size)
}

// required string hash = 3;
inline bool fileDownInfo::_internal_has_hash() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool fileDownInfo::has_hash() const {
  return _internal_has_hash();
}
inline void fileDownInfo::clear_hash() {
  _impl_.hash_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& fileDownInfo::hash() const {
  // @@protoc_insertion_point(field_get:msg.proto.fileDownInfo.hash)
  return _internal_hash();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void fileDownInfo::set_hash(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000002u;
 _impl_.hash_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg.proto.fileDownInfo.hash)
}
inline std::string* fileDownInfo::mutable_hash() {
  std::string* _s = _internal_mutable_hash();
  // @@protoc_insertion_point(field_mutable:msg.proto.fileDownInfo.hash)
  return _s;
}
inline const std::string& fileDownInfo::_internal_hash() const {
  return _impl_.hash_.Get();
}
inline void fileDownInfo::_internal_set_hash(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.hash_.Set(value, GetArenaForAllocation());
}
inline std::string* fileDownInfo::_internal_mutable_hash() {
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.hash_.Mutable(GetArenaForAllocation());
}
inline std::string* fileDownInfo::release_hash() {
  // @@protoc_insertion_point(field_release:msg.proto.fileDownInfo.hash)
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
inline void fileDownInfo::set_allocated_hash(std::string* hash) {
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
  // @@protoc_insertion_point(field_set_allocated:msg.proto.fileDownInfo.hash)
}

// required string humanReadableSize = 4;
inline bool fileDownInfo::_internal_has_humanreadablesize() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool fileDownInfo::has_humanreadablesize() const {
  return _internal_has_humanreadablesize();
}
inline void fileDownInfo::clear_humanreadablesize() {
  _impl_.humanreadablesize_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline const std::string& fileDownInfo::humanreadablesize() const {
  // @@protoc_insertion_point(field_get:msg.proto.fileDownInfo.humanReadableSize)
  return _internal_humanreadablesize();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void fileDownInfo::set_humanreadablesize(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000004u;
 _impl_.humanreadablesize_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg.proto.fileDownInfo.humanReadableSize)
}
inline std::string* fileDownInfo::mutable_humanreadablesize() {
  std::string* _s = _internal_mutable_humanreadablesize();
  // @@protoc_insertion_point(field_mutable:msg.proto.fileDownInfo.humanReadableSize)
  return _s;
}
inline const std::string& fileDownInfo::_internal_humanreadablesize() const {
  return _impl_.humanreadablesize_.Get();
}
inline void fileDownInfo::_internal_set_humanreadablesize(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.humanreadablesize_.Set(value, GetArenaForAllocation());
}
inline std::string* fileDownInfo::_internal_mutable_humanreadablesize() {
  _impl_._has_bits_[0] |= 0x00000004u;
  return _impl_.humanreadablesize_.Mutable(GetArenaForAllocation());
}
inline std::string* fileDownInfo::release_humanreadablesize() {
  // @@protoc_insertion_point(field_release:msg.proto.fileDownInfo.humanReadableSize)
  if (!_internal_has_humanreadablesize()) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000004u;
  auto* p = _impl_.humanreadablesize_.Release();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.humanreadablesize_.IsDefault()) {
    _impl_.humanreadablesize_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return p;
}
inline void fileDownInfo::set_allocated_humanreadablesize(std::string* humanreadablesize) {
  if (humanreadablesize != nullptr) {
    _impl_._has_bits_[0] |= 0x00000004u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000004u;
  }
  _impl_.humanreadablesize_.SetAllocated(humanreadablesize, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.humanreadablesize_.IsDefault()) {
    _impl_.humanreadablesize_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg.proto.fileDownInfo.humanReadableSize)
}

// -------------------------------------------------------------------

// FileDownInfoMsg

// repeated .msg.proto.fileDownInfo fileinfos = 1;
inline int FileDownInfoMsg::_internal_fileinfos_size() const {
  return _impl_.fileinfos_.size();
}
inline int FileDownInfoMsg::fileinfos_size() const {
  return _internal_fileinfos_size();
}
inline void FileDownInfoMsg::clear_fileinfos() {
  _impl_.fileinfos_.Clear();
}
inline ::msg::proto::fileDownInfo* FileDownInfoMsg::mutable_fileinfos(int index) {
  // @@protoc_insertion_point(field_mutable:msg.proto.FileDownInfoMsg.fileinfos)
  return _impl_.fileinfos_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::msg::proto::fileDownInfo >*
FileDownInfoMsg::mutable_fileinfos() {
  // @@protoc_insertion_point(field_mutable_list:msg.proto.FileDownInfoMsg.fileinfos)
  return &_impl_.fileinfos_;
}
inline const ::msg::proto::fileDownInfo& FileDownInfoMsg::_internal_fileinfos(int index) const {
  return _impl_.fileinfos_.Get(index);
}
inline const ::msg::proto::fileDownInfo& FileDownInfoMsg::fileinfos(int index) const {
  // @@protoc_insertion_point(field_get:msg.proto.FileDownInfoMsg.fileinfos)
  return _internal_fileinfos(index);
}
inline ::msg::proto::fileDownInfo* FileDownInfoMsg::_internal_add_fileinfos() {
  return _impl_.fileinfos_.Add();
}
inline ::msg::proto::fileDownInfo* FileDownInfoMsg::add_fileinfos() {
  ::msg::proto::fileDownInfo* _add = _internal_add_fileinfos();
  // @@protoc_insertion_point(field_add:msg.proto.FileDownInfoMsg.fileinfos)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::msg::proto::fileDownInfo >&
FileDownInfoMsg::fileinfos() const {
  // @@protoc_insertion_point(field_list:msg.proto.FileDownInfoMsg.fileinfos)
  return _impl_.fileinfos_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace msg

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_file_5fdown_5finfo_5fmsg_2eproto
