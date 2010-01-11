#ifndef RPROTOBUF_H
#define RPROTOBUF_H

/* should we check this is available */
#include <fcntl.h>
/* FIXME: need to include some header file instead of this define */
#define O_BINARY 0

#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.pb.h>

#define R_NO_REMAP

/* we need to read and write to connections */
#define NEED_CONNECTION_PSTREAMS

#include <Rcpp.h>

#undef GET_NAMES
// #include <R.h>
#include <Rdefines.h>
//#include <Rinternals.h>
#include <R_ext/Callbacks.h>


/* uncomment for debugging */
// #define RPB_DEBUG

#define FIN_DBG(ptr, CLAZZ) 
// #define FIN_DBG(ptr, CLAZZ) Rprintf( "RProtoBuf finalizing %s (%p)\n", CLAZZ, ptr )

#define PRINT_DEBUG_INFO(name,o) \
	Rprintf( "     %s [%d] =     ", name, TYPEOF(o) ) ; \
	Rf_PrintValue( o ) ; \

#define RPROTOBUF_LOOKUP 24
// #define LOOKUP_DEBUG

/* FIXME : quick hack because just using TRUE and FALSE did not work in lookup.cpp */
#define _TRUE_ (Rboolean)TRUE
#define _FALSE_ (Rboolean)FALSE

#define GET_MESSAGE_POINTER_FROM_XP(xp)  (GPB::Message*) EXTPTR_PTR( xp )
#define GET_MESSAGE_POINTER_FROM_S4(m)   (GPB::Message*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_DESCRIPTOR_POINTER_FROM_XP(xp)  (GPB::Descriptor*) EXTPTR_PTR( xp )
#define GET_DESCRIPTOR_POINTER_FROM_S4(m)   (GPB::Descriptor*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_METHOD(xp)  (GPB::MethodDescriptor*) EXTPTR_PTR( xp )

#define COPYSTRING(s) s
#define THROW_SOCKET_ERROR(message) Rf_error( "%s : %s", message, strerror(sockerrno) )

#define XPP EXTPTR_PTR

namespace GPB = google::protobuf;

#define int32 GPB::int32
#define uint32 GPB::uint32
#define int64 GPB::int64
#define uint64 GPB::uint64

#define NEW_S4_OBJECT(CLAZZ) SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS(CLAZZ)) ); \
  		if (!Rf_inherits(oo, CLAZZ)) throwException(CLAZZ, "CannotCreateObjectException" );

namespace rprotobuf{

/* in rprotobuf.cpp */
GPB::Message* PROTOTYPE( const GPB::Descriptor*) ;
GPB::Message* CLONE(const GPB::Message*) ;
RcppExport SEXP do_dollar_Descriptor( SEXP, SEXP ) ;
RcppExport SEXP newProtoMessage( SEXP) ;
RcppExport SEXP getProtobufDescriptor( SEXP ) ;
RcppExport SEXP readProtoFiles( SEXP, SEXP ); 
RcppExport Rboolean isMessage( SEXP, const char* ) ;
RcppExport GPB::FieldDescriptor* getFieldDescriptor(GPB::Message*, SEXP) ;
RcppExport SEXP check_libprotobuf_version( SEXP ) ;
RcppExport SEXP get_protobuf_library_version() ;

/* in constructors.cpp */
void Message_finalizer( SEXP ) ;
RcppExport SEXP new_RS4_Descriptor( const GPB::Descriptor*  ); 
RcppExport SEXP new_RS4_FieldDescriptor( const GPB::FieldDescriptor* ); 
RcppExport SEXP new_RS4_EnumDescriptor( const GPB::EnumDescriptor*); 
RcppExport SEXP new_RS4_Message_( const GPB::Message* );
RcppExport SEXP new_RS4_ServiceDescriptor( const GPB::ServiceDescriptor* ) ;
RcppExport SEXP new_RS4_MethodDescriptor( const GPB::MethodDescriptor* ) ;
RcppExport SEXP new_RS4_FileDescriptor( const GPB::FileDescriptor* ) ;
RcppExport SEXP new_RS4_EnumValueDescriptor( const GPB::EnumValueDescriptor* ) ;

/* in extractors.cpp */
RcppExport SEXP getMessageField( SEXP, SEXP ); 
RcppExport SEXP extractFieldAsSEXP( const GPB::Message *, const GPB::Descriptor*, const GPB::FieldDescriptor* ) ;
RcppExport SEXP get_message_descriptor( SEXP );
RcppExport int MESSAGE_GET_REPEATED_INT( GPB::Message*, GPB::FieldDescriptor*, int) ;
RcppExport double MESSAGE_GET_REPEATED_DOUBLE( GPB::Message*, GPB::FieldDescriptor*, int) ;
RcppExport SEXP get_service_method( SEXP, SEXP) ; 

/* in completion.cpp */
RcppExport SEXP getMessageFieldNames( SEXP) ;
RcppExport SEXP getDescriptorMemberNames( SEXP) ;
RcppExport SEXP getFileDescriptorMemberNames( SEXP) ;
RcppExport SEXP getEnumDescriptorConstantNames( SEXP ) ;
RcppExport SEXP getServiceDescriptorMethodNames( SEXP ) ;

/* in exceptions.cpp */
RcppExport SEXP throwException( const char*, const char*) ;

/* in serialize.cpp */
RcppExport SEXP getMessagePayload( SEXP ) ;
RcppExport std::string getMessagePayloadAs_stdstring( SEXP ) ;
RcppExport SEXP serializeMessageToFile( SEXP , SEXP ) ;
RcppExport SEXP serialize_to_connection( SEXP, SEXP ) ;

/* in lookup.cpp */
RcppExport SEXP newProtocolBufferLookup() ;

/* in mutators.cpp */
RcppExport SEXP setMessageField( SEXP, SEXP, SEXP ) ;
RcppExport int GET_int( SEXP, int ) ;
RcppExport double GET_double( SEXP, int ) ;
RcppExport float GET_float( SEXP, int ) ;
RcppExport int32 GET_int32( SEXP, int) ;
RcppExport int64 GET_int64( SEXP, int) ;
RcppExport uint32 GET_uint32( SEXP, int) ;
RcppExport uint64 GET_uint64( SEXP, int ) ;
RcppExport bool GET_bool( SEXP, int) ;
RcppExport std::string GET_stdstring( SEXP, int ) ;
RcppExport void CHECK_values_for_enum( GPB::FieldDescriptor*, SEXP) ;
RcppExport void CHECK_messages( GPB::FieldDescriptor*, SEXP) ;

/* in aslist.cpp */
RcppExport SEXP as_list_message( SEXP ) ;
RcppExport SEXP as_list_descriptor( SEXP ); 
RcppExport SEXP as_list_enum_descriptor( SEXP );
RcppExport SEXP as_list_file_descriptor( SEXP ) ;
RcppExport SEXP as_list_service_descriptor( SEXP ); 

/* in ascharacter.cpp */
RcppExport SEXP as_character_message( SEXP );
RcppExport SEXP as_character_descriptor( SEXP ); 
RcppExport SEXP as_character_enum_descriptor( SEXP ); 
RcppExport SEXP as_character_field_descriptor(SEXP);
RcppExport SEXP get_value_of_enum( SEXP, SEXP); 
RcppExport SEXP as_character_service_descriptor(SEXP);
RcppExport SEXP as_character_method_descriptor(SEXP);
RcppExport SEXP as_character_file_descriptor( SEXP) ;
RcppExport SEXP as_character_enum_value_descriptor( SEXP) ;

/* in update.cpp */
RcppExport SEXP update_message( SEXP, SEXP) ;

/* in has.cpp */
RcppExport SEXP message_has_field( SEXP, SEXP ); 

/* in clone.cpp */
RcppExport SEXP clone_message( SEXP ) ;

/* in merge.cpp */
RcppExport SEXP merge_message( SEXP, SEXP ); 

/* in read.cpp */
RcppExport SEXP readMessageFromFile( SEXP, SEXP ) ;
RcppExport SEXP readMessageFromConnection( SEXP, SEXP ) ;
RcppExport SEXP readMessageFromRawVector( SEXP, SEXP );

/* in size.cpp */
RcppExport SEXP get_message_bytesize( SEXP ) ;
RcppExport SEXP get_field_size(SEXP, SEXP);
RcppExport SEXP set_field_size(SEXP, SEXP, SEXP);

/* in length.cpp */
RcppExport SEXP get_message_length( SEXP ) ;

/* in initialized.cpp */
RcppExport SEXP is_message_initialized( SEXP ) ;

/* in clear.cpp */
RcppExport SEXP clear_message( SEXP ) ;
RcppExport SEXP clear_message_field( SEXP, SEXP ) ;

/* in swap.cpp */
RcppExport SEXP message_swap_fields(SEXP, SEXP, SEXP, SEXP) ;

/* in set.cpp */
RcppExport SEXP set_field_values( SEXP, SEXP, SEXP, SEXP ) ;
RcppExport SEXP get_field_values( SEXP, SEXP, SEXP) ;

/* in identical.cpp */
RcppExport SEXP identical_messages( SEXP, SEXP) ;
RcppExport SEXP all_equal_messages( SEXP, SEXP, SEXP) ;

/* in add.cpp */
RcppExport SEXP message_add_values( SEXP, SEXP, SEXP);

/* in methods.cpp */
RcppExport SEXP get_method_output_type( SEXP) ;
RcppExport SEXP get_method_input_type( SEXP) ;
RcppExport SEXP get_method_output_prototype( SEXP) ;
RcppExport SEXP get_method_input_prototype( SEXP) ;
RcppExport SEXP valid_input_message( SEXP, SEXP) ;
RcppExport SEXP valid_output_message( SEXP, SEXP) ;

/* in fileDescriptor.cpp */
RcppExport SEXP get_message_file_descriptor( SEXP) ;
RcppExport SEXP get_descriptor_file_descriptor(SEXP) ;
RcppExport SEXP get_enum_file_descriptor(SEXP) ;
RcppExport SEXP get_field_file_descriptor(SEXP) ;
RcppExport SEXP get_service_file_descriptor(SEXP) ;
RcppExport SEXP get_method_file_descriptor(SEXP) ;

/* in name.cpp */
RcppExport SEXP name_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_field_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_enum_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_service_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_method_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_file_descriptor( SEXP ) ;

/* in as.cpp */
RcppExport SEXP asMessage_Descriptor( SEXP ) ;
RcppExport SEXP asMessage_FieldDescriptor( SEXP );
RcppExport SEXP asMessage_EnumDescriptor( SEXP) ;
RcppExport SEXP asMessage_ServiceDescriptor( SEXP ) ;         
RcppExport SEXP asMessage_MethodDescriptor( SEXP ) ;
RcppExport SEXP asMessage_FileDescriptor( SEXP ) ;
RcppExport SEXP asMessage_EnumValueDescriptor( SEXP ) ;

/* in containing_type.cpp */
RcppExport SEXP containing_type__Descriptor( SEXP ); 
RcppExport SEXP containing_type__EnumDescriptor( SEXP ); 
RcppExport SEXP containing_type__FieldDescriptor( SEXP ); 
RcppExport SEXP containing_type__ServiceDescriptor( SEXP ); 
RcppExport SEXP containing_type__MethodDescriptor( SEXP ); 

/* in field_count.cpp */
RcppExport SEXP field_count__Descriptor( SEXP );
RcppExport SEXP nested_type_count__Descriptor( SEXP );
RcppExport SEXP enum_type_count__Descriptor( SEXP );
RcppExport SEXP Descriptor_getFieldByIndex( SEXP, SEXP) ;
RcppExport SEXP Descriptor_getFieldByNumber( SEXP, SEXP ) ;
RcppExport SEXP Descriptor_getFieldByName(SEXP, SEXP) ;
RcppExport SEXP Descriptor_getNestedTypeByIndex( SEXP, SEXP) ;
RcppExport SEXP Descriptor_getNestedTypeByName( SEXP, SEXP); 
RcppExport SEXP Descriptor_getEnumTypeByIndex( SEXP, SEXP);
RcppExport SEXP Descriptor_getEnumTypeByName( SEXP, SEXP);

/* in FieldDescriptor_wrapper.cpp */
RcppExport SEXP FieldDescriptor_is_extension(SEXP) ;
RcppExport SEXP FieldDescriptor_number(SEXP); 
RcppExport SEXP FieldDescriptor_type(SEXP);
RcppExport SEXP FieldDescriptor_cpp_type(SEXP);
RcppExport SEXP FieldDescriptor_label(SEXP );
RcppExport SEXP FieldDescriptor_is_repeated(SEXP);
RcppExport SEXP FieldDescriptor_is_optional(SEXP);
RcppExport SEXP FieldDescriptor_is_required(SEXP);
RcppExport SEXP FieldDescriptor_is_has_default_value(SEXP);
RcppExport SEXP FieldDescriptor_default_value(SEXP);
RcppExport SEXP FieldDescriptor_message_type(SEXP);
RcppExport SEXP FieldDescriptor_enum_type(SEXP); 

/* in EnumDescriptor_wrapper.cpp */
RcppExport SEXP EnumDescriptor_length(SEXP);
RcppExport SEXP EnumDescriptor__value_count(SEXP) ;
RcppExport SEXP EnumDescriptor_getValueByIndex(SEXP, SEXP) ;
RcppExport SEXP EnumDescriptor_getValueByNumber(SEXP, SEXP) ;
RcppExport SEXP EnumDescriptor_getValueByName(SEXP, SEXP);

/* in ServiceDescriptor_wrapper.cpp */
RcppExport SEXP ServiceDescriptor_length(SEXP);
RcppExport SEXP ServiceDescriptor_method_count(SEXP) ;
RcppExport SEXP ServiceDescriptor_getMethodByIndex(SEXP, SEXP) ;
RcppExport SEXP ServiceDescriptor_getMethodByName(SEXP, SEXP) ;

/* in rpc_over_http.cpp */
RcppExport SEXP invoke_method_http( SEXP, SEXP, SEXP, SEXP, SEXP) ;

/* in streams.cpp */
void ZeroCopyInputStreamWrapper_finalizer( SEXP ); 
void ZeroCopyOutputStreamWrapper_finalizer( SEXP ); 

RcppExport SEXP ZeroCopyInputStream_Next(SEXP) ;
RcppExport SEXP ZeroCopyInputStream_BackUp(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ByteCount(SEXP) ;
RcppExport SEXP ZeroCopyInputStream_Skip(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ReadRaw( SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ReadString( SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ReadVarint32( SEXP ) ;
RcppExport SEXP ZeroCopyInputStream_ReadVarint64( SEXP ) ;
RcppExport SEXP ZeroCopyInputStream_ReadLittleEndian32( SEXP ) ;
RcppExport SEXP ZeroCopyInputStream_ReadLittleEndian64( SEXP ) ;

RcppExport SEXP ArrayInputStream_new( SEXP, SEXP ) ;

RcppExport SEXP ArrayOutputStream_new( SEXP, SEXP ) ;

RcppExport SEXP ZeroCopyOutputStream_Next(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyOutputStream_BackUp(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyOutputStream_ByteCount(SEXP) ;
RcppExport SEXP ZeroCopyOutputStream_WriteRaw( SEXP, SEXP);
RcppExport SEXP ZeroCopyOutputStream_WriteString( SEXP, SEXP);
RcppExport SEXP ZeroCopyOutputStream_WriteLittleEndian32( SEXP, SEXP );
RcppExport SEXP ZeroCopyOutputStream_WriteLittleEndian64( SEXP, SEXP );
RcppExport SEXP ZeroCopyOutputStream_WriteVarint32( SEXP, SEXP );
RcppExport SEXP ZeroCopyOutputStream_WriteVarint64( SEXP, SEXP );


RcppExport SEXP FileOutputStream_new( SEXP, SEXP, SEXP) ;
RcppExport SEXP FileOutputStream_Close( SEXP) ;
RcppExport SEXP FileOutputStream_Flush( SEXP) ;
RcppExport SEXP FileOutputStream_GetErrno( SEXP) ;
RcppExport SEXP FileOutputStream_SetCloseOnDelete( SEXP, SEXP ) ;

RcppExport SEXP FileInputStream_new( SEXP, SEXP, SEXP) ;
RcppExport SEXP FileInputStream_Close( SEXP) ;
RcppExport SEXP FileInputStream_GetErrno( SEXP) ;
RcppExport SEXP FileInputStream_SetCloseOnDelete( SEXP, SEXP ) ;

RcppExport SEXP ConnectionInputStream_new( SEXP , SEXP) ;

RcppExport SEXP ConnectionOutputStream_new( SEXP , SEXP) ;

} // namespace rprotobuf


#endif
