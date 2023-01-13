/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 139d44f6c23367eed57c93fafdf7778bd48818e9 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_AtomTerm___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, atom, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Yaep_Term_AtomTerm_toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_BinaryTerm___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, binary, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Yaep_Term_BinaryTerm_toString, 0, 0, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Yaep_Term_BinaryTerm_getSize, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_IntegerTerm___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Yaep_Term_IntegerTerm_getValue arginfo_class_Yaep_Term_BinaryTerm_getSize

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_FloatTerm___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Yaep_Term_FloatTerm_getValue, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_StringTerm___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Yaep_Term_StringTerm_getValue arginfo_class_Yaep_Term_AtomTerm_toString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_TupleTerm___construct, 0, 0, 0)
	ZEND_ARG_VARIADIC_OBJ_INFO(0, items, Yaep\\Term\\AbstractTerm, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Yaep_Term_TupleTerm_getArity arginfo_class_Yaep_Term_BinaryTerm_getSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Yaep_Term_TupleTerm_toArray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Yaep_Term_ListTerm___construct arginfo_class_Yaep_Term_TupleTerm___construct

#define arginfo_class_Yaep_Term_ListTerm_getSize arginfo_class_Yaep_Term_BinaryTerm_getSize

#define arginfo_class_Yaep_Term_ListTerm_toArray arginfo_class_Yaep_Term_TupleTerm_toArray

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Term_MapTerm___construct, 0, 0, 0)
	ZEND_ARG_VARIADIC_OBJ_INFO(0, kvPairs, Yaep\\Term\\AbstractTerm, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Yaep_Term_MapTerm_toArray arginfo_class_Yaep_Term_TupleTerm_toArray

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_NodeInitializationException___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Yaep_NodeConnectionException___construct arginfo_class_Yaep_NodeInitializationException___construct

#define arginfo_class_Yaep_NodeCreateProcessIdentifierException___construct arginfo_class_Yaep_NodeInitializationException___construct

#define arginfo_class_Yaep_MessageReceivingException___construct arginfo_class_Yaep_NodeInitializationException___construct

#define arginfo_class_Yaep_MessageSendingException___construct arginfo_class_Yaep_NodeInitializationException___construct

#define arginfo_class_Yaep_TermEncodingException___construct arginfo_class_Yaep_NodeInitializationException___construct

#define arginfo_class_Yaep_TermDecodingException___construct arginfo_class_Yaep_NodeInitializationException___construct

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Yaep_Connection_getPid, 0, 0, Yaep\\Term\\PidTerm, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Yaep_Connection_receive, 0, 1, Yaep\\Term\\AbstractTerm, 1)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Yaep_Connection_send, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, pid, Yaep\\Term\\PidTerm, 0)
	ZEND_ARG_OBJ_INFO(0, message, Yaep\\Term\\AbstractTerm, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Yaep_Node___construct, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, cookie, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Yaep_Node_connect, 0, 2, Yaep\\Connection, 0)
	ZEND_ARG_TYPE_INFO(0, node, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Yaep_Term_AtomTerm, __construct);
ZEND_METHOD(Yaep_Term_AtomTerm, toString);
ZEND_METHOD(Yaep_Term_BinaryTerm, __construct);
ZEND_METHOD(Yaep_Term_BinaryTerm, toString);
ZEND_METHOD(Yaep_Term_BinaryTerm, getSize);
ZEND_METHOD(Yaep_Term_IntegerTerm, __construct);
ZEND_METHOD(Yaep_Term_IntegerTerm, getValue);
ZEND_METHOD(Yaep_Term_FloatTerm, __construct);
ZEND_METHOD(Yaep_Term_FloatTerm, getValue);
ZEND_METHOD(Yaep_Term_StringTerm, __construct);
ZEND_METHOD(Yaep_Term_StringTerm, getValue);
ZEND_METHOD(Yaep_Term_TupleTerm, __construct);
ZEND_METHOD(Yaep_Term_TupleTerm, getArity);
ZEND_METHOD(Yaep_Term_TupleTerm, toArray);
ZEND_METHOD(Yaep_Term_ListTerm, __construct);
ZEND_METHOD(Yaep_Term_ListTerm, getSize);
ZEND_METHOD(Yaep_Term_ListTerm, toArray);
ZEND_METHOD(Yaep_Term_MapTerm, __construct);
ZEND_METHOD(Yaep_Term_MapTerm, toArray);
ZEND_METHOD(Yaep_NodeInitializationException, __construct);
ZEND_METHOD(Yaep_NodeConnectionException, __construct);
ZEND_METHOD(Yaep_NodeCreateProcessIdentifierException, __construct);
ZEND_METHOD(Yaep_MessageReceivingException, __construct);
ZEND_METHOD(Yaep_MessageSendingException, __construct);
ZEND_METHOD(Yaep_TermEncodingException, __construct);
ZEND_METHOD(Yaep_TermDecodingException, __construct);
ZEND_METHOD(Yaep_Connection, getPid);
ZEND_METHOD(Yaep_Connection, receive);
ZEND_METHOD(Yaep_Connection, send);
ZEND_METHOD(Yaep_Node, __construct);
ZEND_METHOD(Yaep_Node, connect);


static const zend_function_entry class_Yaep_Term_AbstractTerm_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_AtomTerm_methods[] = {
	ZEND_ME(Yaep_Term_AtomTerm, __construct, arginfo_class_Yaep_Term_AtomTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_AtomTerm, toString, arginfo_class_Yaep_Term_AtomTerm_toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_BinaryTerm_methods[] = {
	ZEND_ME(Yaep_Term_BinaryTerm, __construct, arginfo_class_Yaep_Term_BinaryTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_BinaryTerm, toString, arginfo_class_Yaep_Term_BinaryTerm_toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_BinaryTerm, getSize, arginfo_class_Yaep_Term_BinaryTerm_getSize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_BitBinaryTerm_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_IntegerTerm_methods[] = {
	ZEND_ME(Yaep_Term_IntegerTerm, __construct, arginfo_class_Yaep_Term_IntegerTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_IntegerTerm, getValue, arginfo_class_Yaep_Term_IntegerTerm_getValue, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_FloatTerm_methods[] = {
	ZEND_ME(Yaep_Term_FloatTerm, __construct, arginfo_class_Yaep_Term_FloatTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_FloatTerm, getValue, arginfo_class_Yaep_Term_FloatTerm_getValue, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_StringTerm_methods[] = {
	ZEND_ME(Yaep_Term_StringTerm, __construct, arginfo_class_Yaep_Term_StringTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_StringTerm, getValue, arginfo_class_Yaep_Term_StringTerm_getValue, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_TupleTerm_methods[] = {
	ZEND_ME(Yaep_Term_TupleTerm, __construct, arginfo_class_Yaep_Term_TupleTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_TupleTerm, getArity, arginfo_class_Yaep_Term_TupleTerm_getArity, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_TupleTerm, toArray, arginfo_class_Yaep_Term_TupleTerm_toArray, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_ListTerm_methods[] = {
	ZEND_ME(Yaep_Term_ListTerm, __construct, arginfo_class_Yaep_Term_ListTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_ListTerm, getSize, arginfo_class_Yaep_Term_ListTerm_getSize, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_ListTerm, toArray, arginfo_class_Yaep_Term_ListTerm_toArray, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_MapTerm_methods[] = {
	ZEND_ME(Yaep_Term_MapTerm, __construct, arginfo_class_Yaep_Term_MapTerm___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Term_MapTerm, toArray, arginfo_class_Yaep_Term_MapTerm_toArray, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_RefTerm_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_PortTerm_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_FunctionTerm_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Term_PidTerm_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_NodeInitializationException_methods[] = {
	ZEND_ME(Yaep_NodeInitializationException, __construct, arginfo_class_Yaep_NodeInitializationException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_NodeConnectionException_methods[] = {
	ZEND_ME(Yaep_NodeConnectionException, __construct, arginfo_class_Yaep_NodeConnectionException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_NodeCreateProcessIdentifierException_methods[] = {
	ZEND_ME(Yaep_NodeCreateProcessIdentifierException, __construct, arginfo_class_Yaep_NodeCreateProcessIdentifierException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_MessageReceivingException_methods[] = {
	ZEND_ME(Yaep_MessageReceivingException, __construct, arginfo_class_Yaep_MessageReceivingException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_MessageSendingException_methods[] = {
	ZEND_ME(Yaep_MessageSendingException, __construct, arginfo_class_Yaep_MessageSendingException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_TermEncodingException_methods[] = {
	ZEND_ME(Yaep_TermEncodingException, __construct, arginfo_class_Yaep_TermEncodingException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_TermDecodingException_methods[] = {
	ZEND_ME(Yaep_TermDecodingException, __construct, arginfo_class_Yaep_TermDecodingException___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Connection_methods[] = {
	ZEND_ME(Yaep_Connection, getPid, arginfo_class_Yaep_Connection_getPid, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Connection, receive, arginfo_class_Yaep_Connection_receive, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Connection, send, arginfo_class_Yaep_Connection_send, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Yaep_Node_methods[] = {
	ZEND_ME(Yaep_Node, __construct, arginfo_class_Yaep_Node___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Yaep_Node, connect, arginfo_class_Yaep_Node_connect, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Yaep_Term_AbstractTerm(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "AbstractTerm", class_Yaep_Term_AbstractTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_ABSTRACT;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_AtomTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "AtomTerm", class_Yaep_Term_AtomTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_BinaryTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "BinaryTerm", class_Yaep_Term_BinaryTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_BitBinaryTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "BitBinaryTerm", class_Yaep_Term_BitBinaryTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_IntegerTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "IntegerTerm", class_Yaep_Term_IntegerTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_FloatTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "FloatTerm", class_Yaep_Term_FloatTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_StringTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "StringTerm", class_Yaep_Term_StringTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_TupleTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "TupleTerm", class_Yaep_Term_TupleTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_ListTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "ListTerm", class_Yaep_Term_ListTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_MapTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "MapTerm", class_Yaep_Term_MapTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_RefTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "RefTerm", class_Yaep_Term_RefTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_PortTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "PortTerm", class_Yaep_Term_PortTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_FunctionTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "FunctionTerm", class_Yaep_Term_FunctionTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Term_PidTerm(zend_class_entry *class_entry_Yaep_Term_AbstractTerm)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep\\Term", "PidTerm", class_Yaep_Term_PidTerm_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Yaep_Term_AbstractTerm);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_NodeInitializationException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "NodeInitializationException", class_Yaep_NodeInitializationException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_NodeConnectionException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "NodeConnectionException", class_Yaep_NodeConnectionException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_NodeCreateProcessIdentifierException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "NodeCreateProcessIdentifierException", class_Yaep_NodeCreateProcessIdentifierException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_MessageReceivingException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "MessageReceivingException", class_Yaep_MessageReceivingException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_MessageSendingException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "MessageSendingException", class_Yaep_MessageSendingException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_TermEncodingException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "TermEncodingException", class_Yaep_TermEncodingException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_TermDecodingException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "TermDecodingException", class_Yaep_TermDecodingException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Connection(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "Connection", class_Yaep_Connection_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Yaep_Node(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Yaep", "Node", class_Yaep_Node_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}
