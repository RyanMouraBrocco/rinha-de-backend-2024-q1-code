// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: customer_data.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_customer_5fdata_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_customer_5fdata_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_customer_5fdata_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_customer_5fdata_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_customer_5fdata_2eproto;
class CustomerData;
class CustomerDataDefaultTypeInternal;
extern CustomerDataDefaultTypeInternal _CustomerData_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::CustomerData* Arena::CreateMaybeMessage<::CustomerData>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class CustomerData PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:CustomerData) */ {
 public:
  inline CustomerData() : CustomerData(nullptr) {};
  virtual ~CustomerData();

  CustomerData(const CustomerData& from);
  CustomerData(CustomerData&& from) noexcept
    : CustomerData() {
    *this = ::std::move(from);
  }

  inline CustomerData& operator=(const CustomerData& from) {
    CopyFrom(from);
    return *this;
  }
  inline CustomerData& operator=(CustomerData&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const CustomerData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CustomerData* internal_default_instance() {
    return reinterpret_cast<const CustomerData*>(
               &_CustomerData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CustomerData& a, CustomerData& b) {
    a.Swap(&b);
  }
  inline void Swap(CustomerData* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CustomerData* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline CustomerData* New() const final {
    return CreateMaybeMessage<CustomerData>(nullptr);
  }

  CustomerData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CustomerData>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CustomerData& from);
  void MergeFrom(const CustomerData& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CustomerData* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "CustomerData";
  }
  protected:
  explicit CustomerData(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_customer_5fdata_2eproto);
    return ::descriptor_table_customer_5fdata_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLimitFieldNumber = 1,
    kBalanceFieldNumber = 2,
  };
  // int32 limit = 1;
  void clear_limit();
  ::PROTOBUF_NAMESPACE_ID::int32 limit() const;
  void set_limit(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_limit() const;
  void _internal_set_limit(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 balance = 2;
  void clear_balance();
  ::PROTOBUF_NAMESPACE_ID::int32 balance() const;
  void set_balance(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_balance() const;
  void _internal_set_balance(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:CustomerData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int32 limit_;
  ::PROTOBUF_NAMESPACE_ID::int32 balance_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_customer_5fdata_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CustomerData

// int32 limit = 1;
inline void CustomerData::clear_limit() {
  limit_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 CustomerData::_internal_limit() const {
  return limit_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 CustomerData::limit() const {
  // @@protoc_insertion_point(field_get:CustomerData.limit)
  return _internal_limit();
}
inline void CustomerData::_internal_set_limit(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  limit_ = value;
}
inline void CustomerData::set_limit(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_limit(value);
  // @@protoc_insertion_point(field_set:CustomerData.limit)
}

// int32 balance = 2;
inline void CustomerData::clear_balance() {
  balance_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 CustomerData::_internal_balance() const {
  return balance_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 CustomerData::balance() const {
  // @@protoc_insertion_point(field_get:CustomerData.balance)
  return _internal_balance();
}
inline void CustomerData::_internal_set_balance(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  balance_ = value;
}
inline void CustomerData::set_balance(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_balance(value);
  // @@protoc_insertion_point(field_set:CustomerData.balance)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_customer_5fdata_2eproto
