// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: file_down_msg.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_file_5fdown_5fmsg_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_file_5fdown_5fmsg_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_file_5fdown_5fmsg_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_file_5fdown_5fmsg_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_file_5fdown_5fmsg_2eproto;
namespace msg {
namespace proto {
class FileDownMsg;
struct FileDownMsgDefaultTypeInternal;
extern FileDownMsgDefaultTypeInternal _FileDownMsg_default_instance_;
}  // namespace proto
}  // namespace msg
PROTOBUF_NAMESPACE_OPEN
template<> ::msg::proto::FileDownMsg* Arena::CreateMaybeMessage<::msg::proto::FileDownMsg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace msg {
namespace proto {

// ===================================================================

class FileDownMsg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:msg.proto.FileDownMsg) */ {
 public:
  inline FileDownMsg() : FileDownMsg(nullptr) {}
  ~FileDownMsg() override;
  explicit PROTOBUF_CONSTEXPR FileDownMsg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  FileDownMsg(const FileDownMsg& from);
  FileDownMsg(FileDownMsg&& from) noexcept
    : FileDownMsg() {
    *this = ::std::move(from);
  }

  inline FileDownMsg& operator=(const FileDownMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline FileDownMsg& operator=(FileDownMsg&& from) noexcept {
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
  static const FileDownMsg& default_instance() {
    return *internal_default_instance();
  }
  static inline const FileDownMsg* internal_default_instance() {
    return reinterpret_cast<const FileDownMsg*>(
               &_FileDownMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(FileDownMsg& a, FileDownMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(FileDownMsg* other) {
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
  void UnsafeArenaSwap(FileDownMsg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  FileDownMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<FileDownMsg>(arena);
  }
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FileDownMsg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "msg.proto.FileDownMsg";
  }
  protected:
  explicit FileDownMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
    kDataFieldNumber = 4,
    kStartPosFieldNumber = 2,
    kSizeFieldNumber = 3,
    kDataIndexFieldNumber = 5,
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

  // optional bytes data = 4;
  bool has_data() const;
  private:
  bool _internal_has_data() const;
  public:
  void clear_data();
  const std::string& data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_data();
  PROTOBUF_NODISCARD std::string* release_data();
  void set_allocated_data(std::string* data);
  private:
  const std::string& _internal_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_data(const std::string& value);
  std::string* _internal_mutable_data();
  public:

  // required int64 startPos = 2;
  bool has_startpos() const;
  private:
  bool _internal_has_startpos() const;
  public:
  void clear_startpos();
  int64_t startpos() const;
  void set_startpos(int64_t value);
  private:
  int64_t _internal_startpos() const;
  void _internal_set_startpos(int64_t value);
  public:

  // optional int64 size = 3;
  bool has_size() const;
  private:
  bool _internal_has_size() const;
  public:
  void clear_size();
  int64_t size() const;
  void set_size(int64_t value);
  private:
  int64_t _internal_size() const;
  void _internal_set_size(int64_t value);
  public:

  // required int64 dataIndex = 5;
  bool has_dataindex() const;
  private:
  bool _internal_has_dataindex() const;
  public:
  void clear_dataindex();
  int64_t dataindex() const;
  void set_dataindex(int64_t value);
  private:
  int64_t _internal_dataindex() const;
  void _internal_set_dataindex(int64_t value);
  public:

  // @@protoc_insertion_point(class_scope:msg.proto.FileDownMsg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr data_;
    int64_t startpos_;
    int64_t size_;
    int64_t dataindex_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_file_5fdown_5fmsg_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// FileDownMsg

// required string name = 1;
inline bool FileDownMsg::_internal_has_name() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool FileDownMsg::has_name() const {
  return _internal_has_name();
}
inline void FileDownMsg::clear_name() {
  _impl_.name_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& FileDownMsg::name() const {
  // @@protoc_insertion_point(field_get:msg.proto.FileDownMsg.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void FileDownMsg::set_name(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000001u;
 _impl_.name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg.proto.FileDownMsg.name)
}
inline std::string* FileDownMsg::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:msg.proto.FileDownMsg.name)
  return _s;
}
inline const std::string& FileDownMsg::_internal_name() const {
  return _impl_.name_.Get();
}
inline void FileDownMsg::_internal_set_name(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* FileDownMsg::_internal_mutable_name() {
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* FileDownMsg::release_name() {
  // @@protoc_insertion_point(field_release:msg.proto.FileDownMsg.name)
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
inline void FileDownMsg::set_allocated_name(std::string* name) {
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
  // @@protoc_insertion_point(field_set_allocated:msg.proto.FileDownMsg.name)
}

// required int64 startPos = 2;
inline bool FileDownMsg::_internal_has_startpos() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool FileDownMsg::has_startpos() const {
  return _internal_has_startpos();
}
inline void FileDownMsg::clear_startpos() {
  _impl_.startpos_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline int64_t FileDownMsg::_internal_startpos() const {
  return _impl_.startpos_;
}
inline int64_t FileDownMsg::startpos() const {
  // @@protoc_insertion_point(field_get:msg.proto.FileDownMsg.startPos)
  return _internal_startpos();
}
inline void FileDownMsg::_internal_set_startpos(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.startpos_ = value;
}
inline void FileDownMsg::set_startpos(int64_t value) {
  _internal_set_startpos(value);
  // @@protoc_insertion_point(field_set:msg.proto.FileDownMsg.startPos)
}

// optional int64 size = 3;
inline bool FileDownMsg::_internal_has_size() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool FileDownMsg::has_size() const {
  return _internal_has_size();
}
inline void FileDownMsg::clear_size() {
  _impl_.size_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline int64_t FileDownMsg::_internal_size() const {
  return _impl_.size_;
}
inline int64_t FileDownMsg::size() const {
  // @@protoc_insertion_point(field_get:msg.proto.FileDownMsg.size)
  return _internal_size();
}
inline void FileDownMsg::_internal_set_size(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.size_ = value;
}
inline void FileDownMsg::set_size(int64_t value) {
  _internal_set_size(value);
  // @@protoc_insertion_point(field_set:msg.proto.FileDownMsg.size)
}

// optional bytes data = 4;
inline bool FileDownMsg::_internal_has_data() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool FileDownMsg::has_data() const {
  return _internal_has_data();
}
inline void FileDownMsg::clear_data() {
  _impl_.data_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& FileDownMsg::data() const {
  // @@protoc_insertion_point(field_get:msg.proto.FileDownMsg.data)
  return _internal_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void FileDownMsg::set_data(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000002u;
 _impl_.data_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg.proto.FileDownMsg.data)
}
inline std::string* FileDownMsg::mutable_data() {
  std::string* _s = _internal_mutable_data();
  // @@protoc_insertion_point(field_mutable:msg.proto.FileDownMsg.data)
  return _s;
}
inline const std::string& FileDownMsg::_internal_data() const {
  return _impl_.data_.Get();
}
inline void FileDownMsg::_internal_set_data(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.data_.Set(value, GetArenaForAllocation());
}
inline std::string* FileDownMsg::_internal_mutable_data() {
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.data_.Mutable(GetArenaForAllocation());
}
inline std::string* FileDownMsg::release_data() {
  // @@protoc_insertion_point(field_release:msg.proto.FileDownMsg.data)
  if (!_internal_has_data()) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000002u;
  auto* p = _impl_.data_.Release();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.data_.IsDefault()) {
    _impl_.data_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return p;
}
inline void FileDownMsg::set_allocated_data(std::string* data) {
  if (data != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  _impl_.data_.SetAllocated(data, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.data_.IsDefault()) {
    _impl_.data_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg.proto.FileDownMsg.data)
}

// required int64 dataIndex = 5;
inline bool FileDownMsg::_internal_has_dataindex() const {
  bool value = (_impl_._has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool FileDownMsg::has_dataindex() const {
  return _internal_has_dataindex();
}
inline void FileDownMsg::clear_dataindex() {
  _impl_.dataindex_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000010u;
}
inline int64_t FileDownMsg::_internal_dataindex() const {
  return _impl_.dataindex_;
}
inline int64_t FileDownMsg::dataindex() const {
  // @@protoc_insertion_point(field_get:msg.proto.FileDownMsg.dataIndex)
  return _internal_dataindex();
}
inline void FileDownMsg::_internal_set_dataindex(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000010u;
  _impl_.dataindex_ = value;
}
inline void FileDownMsg::set_dataindex(int64_t value) {
  _internal_set_dataindex(value);
  // @@protoc_insertion_point(field_set:msg.proto.FileDownMsg.dataIndex)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace msg

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_file_5fdown_5fmsg_2eproto
