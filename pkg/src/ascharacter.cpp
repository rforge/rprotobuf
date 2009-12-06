#include "rprotobuf.h"

namespace rprotobuf{

SEXP as_character_enum_descriptor( SEXP xp){
#ifdef RPB_DEBUG
Rprintf( "<as_character_enum_descriptor>\n" ) ;
#endif
	
	GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString( d->DebugString().c_str() ) ) ;
	UNPROTECT(1); /* res */
	
#ifdef RPB_DEBUG
Rprintf( "</as_character_enum_descriptor>\n" ) ;
#endif
	return(res);
}


SEXP as_character_field_descriptor( SEXP xp){
#ifdef RPB_DEBUG
Rprintf( "<as_character_field_descriptor>\n" ) ;
#endif
	
	GPB::FieldDescriptor* d = (GPB::FieldDescriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString( d->DebugString().c_str() ) ) ;
	UNPROTECT(1); /* res */
	
#ifdef RPB_DEBUG
Rprintf( "</as_character_field_descriptor>\n" ) ;
#endif
	return(res);
}

SEXP as_character_file_descriptor( SEXP xp){
#ifdef RPB_DEBUG
Rprintf( "<as_character_file_descriptor>\n" ) ;
#endif
	
	GPB::FileDescriptor* d = (GPB::FileDescriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString( d->DebugString().c_str() ) ) ;
	UNPROTECT(1); /* res */
	
#ifdef RPB_DEBUG
Rprintf( "</as_character_file_descriptor>\n" ) ;
#endif
	return(res);
}

SEXP as_character_enum_value_descriptor( SEXP xp){
	GPB::EnumValueDescriptor* d = (GPB::EnumValueDescriptor*)EXTPTR_PTR(xp) ;
	return Rf_mkString( d->DebugString().c_str() ) ;
}

/**
 * Get the debug string of a message
 *
 * @param xp external pointer to a Message pointer
 */
SEXP as_character_message( SEXP xp ){
	
	/* grab the Message pointer */
	GPB::Message* message = (GPB::Message*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString(message->DebugString().c_str() ) ) ; 
	UNPROTECT(1); /* res */
	return res ;
}


/**
 * Get the debug string of a message
 *
 * @param xp external pointer to a Descriptor pointer
 */
SEXP as_character_descriptor( SEXP xp ){
	
	/* grab the Message pointer */
	GPB::Descriptor* desc = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString(desc->DebugString().c_str() ) ) ; 
	UNPROTECT(1); /* res */
	return res ;
}

/**
 * Get the debug string of a service descriptor
 *
 * @param xp (GPB::ServiceDescriptor*) external pointer
 */
SEXP as_character_service_descriptor( SEXP xp ){
	
	/* grab the Message pointer */
	GPB::ServiceDescriptor* desc = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString(desc->DebugString().c_str() ) ) ; 
	UNPROTECT(1); /* res */
	return res ;
}

/**
 * Get the debug string of a method descriptor
 *
 * @param xp (GPB::MethodDescriptor*) external pointer
 */
SEXP as_character_method_descriptor( SEXP xp ){
	
	/* grab the Message pointer */
	GPB::MethodDescriptor* desc = (GPB::MethodDescriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString(desc->DebugString().c_str() ) ) ; 
	UNPROTECT(1); /* res */
	return res ;
}



/**
 * Get the value of the enum called name
 *
 * @param xp external pointer to an EnumDescriptor
 * @param name the name of the enum
 * 
 * @param the value associated with the name
 */
SEXP get_value_of_enum( SEXP xp, SEXP name ){
#ifdef RPB_DEBUG
Rprintf( "<get_value_of_enum>\n" ) ;
#endif
	
	GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
	
	/* only the first one is used */
	std::string val = CHAR( STRING_ELT( name, 0) ) ;
	const GPB::EnumValueDescriptor* evd = d->FindValueByName(val) ;
    if( !evd ){
    	/* or maybe it should just be NA */
    	throwException( "cannot get the value", "UnknownEnumValueException" ) ;
    }
	
	SEXP res = PROTECT( Rf_allocVector(INTSXP, 1 ) ) ;
	INTEGER(res)[0] = evd->number() ;
	UNPROTECT(1); /* res */
	
#ifdef RPB_DEBUG
Rprintf( "</get_value_of_enum>\n" ) ;
#endif
	
	return res ;
}

} // namespace rprotobuf

