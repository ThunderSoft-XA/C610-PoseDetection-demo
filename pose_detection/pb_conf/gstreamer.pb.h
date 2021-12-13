// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gstreamer.proto

#ifndef PROTOBUF_gstreamer_2eproto__INCLUDED
#define PROTOBUF_gstreamer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace gstcfg {
class DataInfo;
class DataInfoDefaultTypeInternal;
extern DataInfoDefaultTypeInternal _DataInfo_default_instance_;
class DataSource;
class DataSourceDefaultTypeInternal;
extern DataSourceDefaultTypeInternal _DataSource_default_instance_;
class DataSourceSet;
class DataSourceSetDefaultTypeInternal;
extern DataSourceSetDefaultTypeInternal _DataSourceSet_default_instance_;
}  // namespace gstcfg

namespace gstcfg {

namespace protobuf_gstreamer_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_gstreamer_2eproto

enum GstType {
  LOCAL = 0,
  CAMERA = 1,
  RTSP = 2,
  GstType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  GstType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool GstType_IsValid(int value);
const GstType GstType_MIN = LOCAL;
const GstType GstType_MAX = RTSP;
const int GstType_ARRAYSIZE = GstType_MAX + 1;

const ::google::protobuf::EnumDescriptor* GstType_descriptor();
inline const ::std::string& GstType_Name(GstType value) {
  return ::google::protobuf::internal::NameOfEnum(
    GstType_descriptor(), value);
}
inline bool GstType_Parse(
    const ::std::string& name, GstType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GstType>(
    GstType_descriptor(), name, value);
}
// ===================================================================

class DataInfo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gstcfg.DataInfo) */ {
 public:
  DataInfo();
  virtual ~DataInfo();

  DataInfo(const DataInfo& from);

  inline DataInfo& operator=(const DataInfo& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DataInfo& default_instance();

  static inline const DataInfo* internal_default_instance() {
    return reinterpret_cast<const DataInfo*>(
               &_DataInfo_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(DataInfo* other);

  // implements Message ----------------------------------------------

  inline DataInfo* New() const PROTOBUF_FINAL { return New(NULL); }

  DataInfo* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const DataInfo& from);
  void MergeFrom(const DataInfo& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(DataInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string format = 5;
  void clear_format();
  static const int kFormatFieldNumber = 5;
  const ::std::string& format() const;
  void set_format(const ::std::string& value);
  #if LANG_CXX11
  void set_format(::std::string&& value);
  #endif
  void set_format(const char* value);
  void set_format(const char* value, size_t size);
  ::std::string* mutable_format();
  ::std::string* release_format();
  void set_allocated_format(::std::string* format);

  // string decode = 6;
  void clear_decode();
  static const int kDecodeFieldNumber = 6;
  const ::std::string& decode() const;
  void set_decode(const ::std::string& value);
  #if LANG_CXX11
  void set_decode(::std::string&& value);
  #endif
  void set_decode(const char* value);
  void set_decode(const char* value, size_t size);
  ::std::string* mutable_decode();
  ::std::string* release_decode();
  void set_allocated_decode(::std::string* decode);

  // int32 width = 1;
  void clear_width();
  static const int kWidthFieldNumber = 1;
  ::google::protobuf::int32 width() const;
  void set_width(::google::protobuf::int32 value);

  // int32 height = 2;
  void clear_height();
  static const int kHeightFieldNumber = 2;
  ::google::protobuf::int32 height() const;
  void set_height(::google::protobuf::int32 value);

  // int32 channel = 3;
  void clear_channel();
  static const int kChannelFieldNumber = 3;
  ::google::protobuf::int32 channel() const;
  void set_channel(::google::protobuf::int32 value);

  // int32 framerate = 4;
  void clear_framerate();
  static const int kFramerateFieldNumber = 4;
  ::google::protobuf::int32 framerate() const;
  void set_framerate(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:gstcfg.DataInfo)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr format_;
  ::google::protobuf::internal::ArenaStringPtr decode_;
  ::google::protobuf::int32 width_;
  ::google::protobuf::int32 height_;
  ::google::protobuf::int32 channel_;
  ::google::protobuf::int32 framerate_;
  mutable int _cached_size_;
  friend struct protobuf_gstreamer_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class DataSource : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gstcfg.DataSource) */ {
 public:
  DataSource();
  virtual ~DataSource();

  DataSource(const DataSource& from);

  inline DataSource& operator=(const DataSource& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DataSource& default_instance();

  static inline const DataSource* internal_default_instance() {
    return reinterpret_cast<const DataSource*>(
               &_DataSource_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(DataSource* other);

  // implements Message ----------------------------------------------

  inline DataSource* New() const PROTOBUF_FINAL { return New(NULL); }

  DataSource* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const DataSource& from);
  void MergeFrom(const DataSource& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(DataSource* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string gst_name = 2;
  void clear_gst_name();
  static const int kGstNameFieldNumber = 2;
  const ::std::string& gst_name() const;
  void set_gst_name(const ::std::string& value);
  #if LANG_CXX11
  void set_gst_name(::std::string&& value);
  #endif
  void set_gst_name(const char* value);
  void set_gst_name(const char* value, size_t size);
  ::std::string* mutable_gst_name();
  ::std::string* release_gst_name();
  void set_allocated_gst_name(::std::string* gst_name);

  // string gst_path = 4;
  void clear_gst_path();
  static const int kGstPathFieldNumber = 4;
  const ::std::string& gst_path() const;
  void set_gst_path(const ::std::string& value);
  #if LANG_CXX11
  void set_gst_path(::std::string&& value);
  #endif
  void set_gst_path(const char* value);
  void set_gst_path(const char* value, size_t size);
  ::std::string* mutable_gst_path();
  ::std::string* release_gst_path();
  void set_allocated_gst_path(::std::string* gst_path);

  // string sink_name = 5;
  void clear_sink_name();
  static const int kSinkNameFieldNumber = 5;
  const ::std::string& sink_name() const;
  void set_sink_name(const ::std::string& value);
  #if LANG_CXX11
  void set_sink_name(::std::string&& value);
  #endif
  void set_sink_name(const char* value);
  void set_sink_name(const char* value, size_t size);
  ::std::string* mutable_sink_name();
  ::std::string* release_sink_name();
  void set_allocated_sink_name(::std::string* sink_name);

  // .gstcfg.DataInfo data_info = 6;
  bool has_data_info() const;
  void clear_data_info();
  static const int kDataInfoFieldNumber = 6;
  const ::gstcfg::DataInfo& data_info() const;
  ::gstcfg::DataInfo* mutable_data_info();
  ::gstcfg::DataInfo* release_data_info();
  void set_allocated_data_info(::gstcfg::DataInfo* data_info);

  // int32 gst_id = 1;
  void clear_gst_id();
  static const int kGstIdFieldNumber = 1;
  ::google::protobuf::int32 gst_id() const;
  void set_gst_id(::google::protobuf::int32 value);

  // .gstcfg.GstType gst_type = 3;
  void clear_gst_type();
  static const int kGstTypeFieldNumber = 3;
  ::gstcfg::GstType gst_type() const;
  void set_gst_type(::gstcfg::GstType value);

  // bool neeed_calib = 7;
  void clear_neeed_calib();
  static const int kNeeedCalibFieldNumber = 7;
  bool neeed_calib() const;
  void set_neeed_calib(bool value);

  // bool enable_ai = 8;
  void clear_enable_ai();
  static const int kEnableAiFieldNumber = 8;
  bool enable_ai() const;
  void set_enable_ai(bool value);

  // @@protoc_insertion_point(class_scope:gstcfg.DataSource)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr gst_name_;
  ::google::protobuf::internal::ArenaStringPtr gst_path_;
  ::google::protobuf::internal::ArenaStringPtr sink_name_;
  ::gstcfg::DataInfo* data_info_;
  ::google::protobuf::int32 gst_id_;
  int gst_type_;
  bool neeed_calib_;
  bool enable_ai_;
  mutable int _cached_size_;
  friend struct protobuf_gstreamer_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class DataSourceSet : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gstcfg.DataSourceSet) */ {
 public:
  DataSourceSet();
  virtual ~DataSourceSet();

  DataSourceSet(const DataSourceSet& from);

  inline DataSourceSet& operator=(const DataSourceSet& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DataSourceSet& default_instance();

  static inline const DataSourceSet* internal_default_instance() {
    return reinterpret_cast<const DataSourceSet*>(
               &_DataSourceSet_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(DataSourceSet* other);

  // implements Message ----------------------------------------------

  inline DataSourceSet* New() const PROTOBUF_FINAL { return New(NULL); }

  DataSourceSet* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const DataSourceSet& from);
  void MergeFrom(const DataSourceSet& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(DataSourceSet* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .gstcfg.DataSource data_source = 1;
  int data_source_size() const;
  void clear_data_source();
  static const int kDataSourceFieldNumber = 1;
  const ::gstcfg::DataSource& data_source(int index) const;
  ::gstcfg::DataSource* mutable_data_source(int index);
  ::gstcfg::DataSource* add_data_source();
  ::google::protobuf::RepeatedPtrField< ::gstcfg::DataSource >*
      mutable_data_source();
  const ::google::protobuf::RepeatedPtrField< ::gstcfg::DataSource >&
      data_source() const;

  // @@protoc_insertion_point(class_scope:gstcfg.DataSourceSet)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::gstcfg::DataSource > data_source_;
  mutable int _cached_size_;
  friend struct protobuf_gstreamer_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// DataInfo

// int32 width = 1;
inline void DataInfo::clear_width() {
  width_ = 0;
}
inline ::google::protobuf::int32 DataInfo::width() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataInfo.width)
  return width_;
}
inline void DataInfo::set_width(::google::protobuf::int32 value) {
  
  width_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataInfo.width)
}

// int32 height = 2;
inline void DataInfo::clear_height() {
  height_ = 0;
}
inline ::google::protobuf::int32 DataInfo::height() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataInfo.height)
  return height_;
}
inline void DataInfo::set_height(::google::protobuf::int32 value) {
  
  height_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataInfo.height)
}

// int32 channel = 3;
inline void DataInfo::clear_channel() {
  channel_ = 0;
}
inline ::google::protobuf::int32 DataInfo::channel() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataInfo.channel)
  return channel_;
}
inline void DataInfo::set_channel(::google::protobuf::int32 value) {
  
  channel_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataInfo.channel)
}

// int32 framerate = 4;
inline void DataInfo::clear_framerate() {
  framerate_ = 0;
}
inline ::google::protobuf::int32 DataInfo::framerate() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataInfo.framerate)
  return framerate_;
}
inline void DataInfo::set_framerate(::google::protobuf::int32 value) {
  
  framerate_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataInfo.framerate)
}

// string format = 5;
inline void DataInfo::clear_format() {
  format_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DataInfo::format() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataInfo.format)
  return format_.GetNoArena();
}
inline void DataInfo::set_format(const ::std::string& value) {
  
  format_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:gstcfg.DataInfo.format)
}
#if LANG_CXX11
inline void DataInfo::set_format(::std::string&& value) {
  
  format_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gstcfg.DataInfo.format)
}
#endif
inline void DataInfo::set_format(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  format_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gstcfg.DataInfo.format)
}
inline void DataInfo::set_format(const char* value, size_t size) {
  
  format_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gstcfg.DataInfo.format)
}
inline ::std::string* DataInfo::mutable_format() {
  
  // @@protoc_insertion_point(field_mutable:gstcfg.DataInfo.format)
  return format_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DataInfo::release_format() {
  // @@protoc_insertion_point(field_release:gstcfg.DataInfo.format)
  
  return format_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DataInfo::set_allocated_format(::std::string* format) {
  if (format != NULL) {
    
  } else {
    
  }
  format_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), format);
  // @@protoc_insertion_point(field_set_allocated:gstcfg.DataInfo.format)
}

// string decode = 6;
inline void DataInfo::clear_decode() {
  decode_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DataInfo::decode() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataInfo.decode)
  return decode_.GetNoArena();
}
inline void DataInfo::set_decode(const ::std::string& value) {
  
  decode_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:gstcfg.DataInfo.decode)
}
#if LANG_CXX11
inline void DataInfo::set_decode(::std::string&& value) {
  
  decode_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gstcfg.DataInfo.decode)
}
#endif
inline void DataInfo::set_decode(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  decode_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gstcfg.DataInfo.decode)
}
inline void DataInfo::set_decode(const char* value, size_t size) {
  
  decode_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gstcfg.DataInfo.decode)
}
inline ::std::string* DataInfo::mutable_decode() {
  
  // @@protoc_insertion_point(field_mutable:gstcfg.DataInfo.decode)
  return decode_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DataInfo::release_decode() {
  // @@protoc_insertion_point(field_release:gstcfg.DataInfo.decode)
  
  return decode_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DataInfo::set_allocated_decode(::std::string* decode) {
  if (decode != NULL) {
    
  } else {
    
  }
  decode_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), decode);
  // @@protoc_insertion_point(field_set_allocated:gstcfg.DataInfo.decode)
}

// -------------------------------------------------------------------

// DataSource

// int32 gst_id = 1;
inline void DataSource::clear_gst_id() {
  gst_id_ = 0;
}
inline ::google::protobuf::int32 DataSource::gst_id() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.gst_id)
  return gst_id_;
}
inline void DataSource::set_gst_id(::google::protobuf::int32 value) {
  
  gst_id_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.gst_id)
}

// string gst_name = 2;
inline void DataSource::clear_gst_name() {
  gst_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DataSource::gst_name() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.gst_name)
  return gst_name_.GetNoArena();
}
inline void DataSource::set_gst_name(const ::std::string& value) {
  
  gst_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.gst_name)
}
#if LANG_CXX11
inline void DataSource::set_gst_name(::std::string&& value) {
  
  gst_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gstcfg.DataSource.gst_name)
}
#endif
inline void DataSource::set_gst_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  gst_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gstcfg.DataSource.gst_name)
}
inline void DataSource::set_gst_name(const char* value, size_t size) {
  
  gst_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gstcfg.DataSource.gst_name)
}
inline ::std::string* DataSource::mutable_gst_name() {
  
  // @@protoc_insertion_point(field_mutable:gstcfg.DataSource.gst_name)
  return gst_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DataSource::release_gst_name() {
  // @@protoc_insertion_point(field_release:gstcfg.DataSource.gst_name)
  
  return gst_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DataSource::set_allocated_gst_name(::std::string* gst_name) {
  if (gst_name != NULL) {
    
  } else {
    
  }
  gst_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), gst_name);
  // @@protoc_insertion_point(field_set_allocated:gstcfg.DataSource.gst_name)
}

// .gstcfg.GstType gst_type = 3;
inline void DataSource::clear_gst_type() {
  gst_type_ = 0;
}
inline ::gstcfg::GstType DataSource::gst_type() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.gst_type)
  return static_cast< ::gstcfg::GstType >(gst_type_);
}
inline void DataSource::set_gst_type(::gstcfg::GstType value) {
  
  gst_type_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.gst_type)
}

// string gst_path = 4;
inline void DataSource::clear_gst_path() {
  gst_path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DataSource::gst_path() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.gst_path)
  return gst_path_.GetNoArena();
}
inline void DataSource::set_gst_path(const ::std::string& value) {
  
  gst_path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.gst_path)
}
#if LANG_CXX11
inline void DataSource::set_gst_path(::std::string&& value) {
  
  gst_path_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gstcfg.DataSource.gst_path)
}
#endif
inline void DataSource::set_gst_path(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  gst_path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gstcfg.DataSource.gst_path)
}
inline void DataSource::set_gst_path(const char* value, size_t size) {
  
  gst_path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gstcfg.DataSource.gst_path)
}
inline ::std::string* DataSource::mutable_gst_path() {
  
  // @@protoc_insertion_point(field_mutable:gstcfg.DataSource.gst_path)
  return gst_path_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DataSource::release_gst_path() {
  // @@protoc_insertion_point(field_release:gstcfg.DataSource.gst_path)
  
  return gst_path_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DataSource::set_allocated_gst_path(::std::string* gst_path) {
  if (gst_path != NULL) {
    
  } else {
    
  }
  gst_path_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), gst_path);
  // @@protoc_insertion_point(field_set_allocated:gstcfg.DataSource.gst_path)
}

// string sink_name = 5;
inline void DataSource::clear_sink_name() {
  sink_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DataSource::sink_name() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.sink_name)
  return sink_name_.GetNoArena();
}
inline void DataSource::set_sink_name(const ::std::string& value) {
  
  sink_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.sink_name)
}
#if LANG_CXX11
inline void DataSource::set_sink_name(::std::string&& value) {
  
  sink_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gstcfg.DataSource.sink_name)
}
#endif
inline void DataSource::set_sink_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  sink_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gstcfg.DataSource.sink_name)
}
inline void DataSource::set_sink_name(const char* value, size_t size) {
  
  sink_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gstcfg.DataSource.sink_name)
}
inline ::std::string* DataSource::mutable_sink_name() {
  
  // @@protoc_insertion_point(field_mutable:gstcfg.DataSource.sink_name)
  return sink_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DataSource::release_sink_name() {
  // @@protoc_insertion_point(field_release:gstcfg.DataSource.sink_name)
  
  return sink_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DataSource::set_allocated_sink_name(::std::string* sink_name) {
  if (sink_name != NULL) {
    
  } else {
    
  }
  sink_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sink_name);
  // @@protoc_insertion_point(field_set_allocated:gstcfg.DataSource.sink_name)
}

// .gstcfg.DataInfo data_info = 6;
inline bool DataSource::has_data_info() const {
  return this != internal_default_instance() && data_info_ != NULL;
}
inline void DataSource::clear_data_info() {
  if (GetArenaNoVirtual() == NULL && data_info_ != NULL) delete data_info_;
  data_info_ = NULL;
}
inline const ::gstcfg::DataInfo& DataSource::data_info() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.data_info)
  return data_info_ != NULL ? *data_info_
                         : *::gstcfg::DataInfo::internal_default_instance();
}
inline ::gstcfg::DataInfo* DataSource::mutable_data_info() {
  
  if (data_info_ == NULL) {
    data_info_ = new ::gstcfg::DataInfo;
  }
  // @@protoc_insertion_point(field_mutable:gstcfg.DataSource.data_info)
  return data_info_;
}
inline ::gstcfg::DataInfo* DataSource::release_data_info() {
  // @@protoc_insertion_point(field_release:gstcfg.DataSource.data_info)
  
  ::gstcfg::DataInfo* temp = data_info_;
  data_info_ = NULL;
  return temp;
}
inline void DataSource::set_allocated_data_info(::gstcfg::DataInfo* data_info) {
  delete data_info_;
  data_info_ = data_info;
  if (data_info) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:gstcfg.DataSource.data_info)
}

// bool neeed_calib = 7;
inline void DataSource::clear_neeed_calib() {
  neeed_calib_ = false;
}
inline bool DataSource::neeed_calib() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.neeed_calib)
  return neeed_calib_;
}
inline void DataSource::set_neeed_calib(bool value) {
  
  neeed_calib_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.neeed_calib)
}

// bool enable_ai = 8;
inline void DataSource::clear_enable_ai() {
  enable_ai_ = false;
}
inline bool DataSource::enable_ai() const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSource.enable_ai)
  return enable_ai_;
}
inline void DataSource::set_enable_ai(bool value) {
  
  enable_ai_ = value;
  // @@protoc_insertion_point(field_set:gstcfg.DataSource.enable_ai)
}

// -------------------------------------------------------------------

// DataSourceSet

// repeated .gstcfg.DataSource data_source = 1;
inline int DataSourceSet::data_source_size() const {
  return data_source_.size();
}
inline void DataSourceSet::clear_data_source() {
  data_source_.Clear();
}
inline const ::gstcfg::DataSource& DataSourceSet::data_source(int index) const {
  // @@protoc_insertion_point(field_get:gstcfg.DataSourceSet.data_source)
  return data_source_.Get(index);
}
inline ::gstcfg::DataSource* DataSourceSet::mutable_data_source(int index) {
  // @@protoc_insertion_point(field_mutable:gstcfg.DataSourceSet.data_source)
  return data_source_.Mutable(index);
}
inline ::gstcfg::DataSource* DataSourceSet::add_data_source() {
  // @@protoc_insertion_point(field_add:gstcfg.DataSourceSet.data_source)
  return data_source_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::gstcfg::DataSource >*
DataSourceSet::mutable_data_source() {
  // @@protoc_insertion_point(field_mutable_list:gstcfg.DataSourceSet.data_source)
  return &data_source_;
}
inline const ::google::protobuf::RepeatedPtrField< ::gstcfg::DataSource >&
DataSourceSet::data_source() const {
  // @@protoc_insertion_point(field_list:gstcfg.DataSourceSet.data_source)
  return data_source_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace gstcfg

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::gstcfg::GstType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gstcfg::GstType>() {
  return ::gstcfg::GstType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_gstreamer_2eproto__INCLUDED
