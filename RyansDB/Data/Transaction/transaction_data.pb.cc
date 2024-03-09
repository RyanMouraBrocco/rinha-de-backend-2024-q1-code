// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: transaction_data.proto

#include "transaction_data.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2ftimestamp_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Timestamp_google_2fprotobuf_2ftimestamp_2eproto;
class TransactionDataDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<TransactionData> _instance;
} _TransactionData_default_instance_;
static void InitDefaultsscc_info_TransactionData_transaction_5fdata_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_TransactionData_default_instance_;
    new (ptr) ::TransactionData();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::TransactionData::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_TransactionData_transaction_5fdata_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_TransactionData_transaction_5fdata_2eproto}, {
      &scc_info_Timestamp_google_2fprotobuf_2ftimestamp_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_transaction_5fdata_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_transaction_5fdata_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_transaction_5fdata_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_transaction_5fdata_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::TransactionData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::TransactionData, value_),
  PROTOBUF_FIELD_OFFSET(::TransactionData, iscredit_),
  PROTOBUF_FIELD_OFFSET(::TransactionData, description_),
  PROTOBUF_FIELD_OFFSET(::TransactionData, createdate_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::TransactionData)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_TransactionData_default_instance_),
};

const char descriptor_table_protodef_transaction_5fdata_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026transaction_data.proto\032\037google/protobu"
  "f/timestamp.proto\"w\n\017TransactionData\022\r\n\005"
  "value\030\001 \001(\005\022\020\n\010isCredit\030\002 \001(\010\022\023\n\013descrip"
  "tion\030\003 \001(\t\022.\n\ncreateDate\030\004 \001(\0132\032.google."
  "protobuf.Timestampb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_transaction_5fdata_2eproto_deps[1] = {
  &::descriptor_table_google_2fprotobuf_2ftimestamp_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_transaction_5fdata_2eproto_sccs[1] = {
  &scc_info_TransactionData_transaction_5fdata_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_transaction_5fdata_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_transaction_5fdata_2eproto = {
  false, false, descriptor_table_protodef_transaction_5fdata_2eproto, "transaction_data.proto", 186,
  &descriptor_table_transaction_5fdata_2eproto_once, descriptor_table_transaction_5fdata_2eproto_sccs, descriptor_table_transaction_5fdata_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_transaction_5fdata_2eproto::offsets,
  file_level_metadata_transaction_5fdata_2eproto, 1, file_level_enum_descriptors_transaction_5fdata_2eproto, file_level_service_descriptors_transaction_5fdata_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_transaction_5fdata_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_transaction_5fdata_2eproto)), true);

// ===================================================================

void TransactionData::InitAsDefaultInstance() {
  ::_TransactionData_default_instance_._instance.get_mutable()->createdate_ = const_cast< PROTOBUF_NAMESPACE_ID::Timestamp*>(
      PROTOBUF_NAMESPACE_ID::Timestamp::internal_default_instance());
}
class TransactionData::_Internal {
 public:
  static const PROTOBUF_NAMESPACE_ID::Timestamp& createdate(const TransactionData* msg);
};

const PROTOBUF_NAMESPACE_ID::Timestamp&
TransactionData::_Internal::createdate(const TransactionData* msg) {
  return *msg->createdate_;
}
void TransactionData::clear_createdate() {
  if (GetArena() == nullptr && createdate_ != nullptr) {
    delete createdate_;
  }
  createdate_ = nullptr;
}
TransactionData::TransactionData(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:TransactionData)
}
TransactionData::TransactionData(const TransactionData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  description_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_description().empty()) {
    description_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_description(),
      GetArena());
  }
  if (from._internal_has_createdate()) {
    createdate_ = new PROTOBUF_NAMESPACE_ID::Timestamp(*from.createdate_);
  } else {
    createdate_ = nullptr;
  }
  ::memcpy(&value_, &from.value_,
    static_cast<size_t>(reinterpret_cast<char*>(&iscredit_) -
    reinterpret_cast<char*>(&value_)) + sizeof(iscredit_));
  // @@protoc_insertion_point(copy_constructor:TransactionData)
}

void TransactionData::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_TransactionData_transaction_5fdata_2eproto.base);
  description_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&createdate_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&iscredit_) -
      reinterpret_cast<char*>(&createdate_)) + sizeof(iscredit_));
}

TransactionData::~TransactionData() {
  // @@protoc_insertion_point(destructor:TransactionData)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void TransactionData::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  description_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete createdate_;
}

void TransactionData::ArenaDtor(void* object) {
  TransactionData* _this = reinterpret_cast< TransactionData* >(object);
  (void)_this;
}
void TransactionData::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void TransactionData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const TransactionData& TransactionData::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_TransactionData_transaction_5fdata_2eproto.base);
  return *internal_default_instance();
}


void TransactionData::Clear() {
// @@protoc_insertion_point(message_clear_start:TransactionData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  description_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  if (GetArena() == nullptr && createdate_ != nullptr) {
    delete createdate_;
  }
  createdate_ = nullptr;
  ::memset(&value_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&iscredit_) -
      reinterpret_cast<char*>(&value_)) + sizeof(iscredit_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* TransactionData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 value = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          value_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bool isCredit = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          iscredit_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string description = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_description();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "TransactionData.description"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .google.protobuf.Timestamp createDate = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr = ctx->ParseMessage(_internal_mutable_createdate(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* TransactionData::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:TransactionData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 value = 1;
  if (this->value() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_value(), target);
  }

  // bool isCredit = 2;
  if (this->iscredit() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(2, this->_internal_iscredit(), target);
  }

  // string description = 3;
  if (this->description().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_description().data(), static_cast<int>(this->_internal_description().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "TransactionData.description");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_description(), target);
  }

  // .google.protobuf.Timestamp createDate = 4;
  if (this->has_createdate()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        4, _Internal::createdate(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:TransactionData)
  return target;
}

size_t TransactionData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:TransactionData)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string description = 3;
  if (this->description().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_description());
  }

  // .google.protobuf.Timestamp createDate = 4;
  if (this->has_createdate()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *createdate_);
  }

  // int32 value = 1;
  if (this->value() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_value());
  }

  // bool isCredit = 2;
  if (this->iscredit() != 0) {
    total_size += 1 + 1;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void TransactionData::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:TransactionData)
  GOOGLE_DCHECK_NE(&from, this);
  const TransactionData* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<TransactionData>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:TransactionData)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:TransactionData)
    MergeFrom(*source);
  }
}

void TransactionData::MergeFrom(const TransactionData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:TransactionData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.description().size() > 0) {
    _internal_set_description(from._internal_description());
  }
  if (from.has_createdate()) {
    _internal_mutable_createdate()->PROTOBUF_NAMESPACE_ID::Timestamp::MergeFrom(from._internal_createdate());
  }
  if (from.value() != 0) {
    _internal_set_value(from._internal_value());
  }
  if (from.iscredit() != 0) {
    _internal_set_iscredit(from._internal_iscredit());
  }
}

void TransactionData::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:TransactionData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TransactionData::CopyFrom(const TransactionData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:TransactionData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TransactionData::IsInitialized() const {
  return true;
}

void TransactionData::InternalSwap(TransactionData* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  description_.Swap(&other->description_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(TransactionData, iscredit_)
      + sizeof(TransactionData::iscredit_)
      - PROTOBUF_FIELD_OFFSET(TransactionData, createdate_)>(
          reinterpret_cast<char*>(&createdate_),
          reinterpret_cast<char*>(&other->createdate_));
}

::PROTOBUF_NAMESPACE_ID::Metadata TransactionData::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::TransactionData* Arena::CreateMaybeMessage< ::TransactionData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::TransactionData >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
