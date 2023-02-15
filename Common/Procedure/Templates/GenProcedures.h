#pragma once
#include "Types.h"
#include <Windows.h>
#include "DBBind.h"

{%- macro gen_procedures() -%} {% include 'Procedure.h' %} {% endmacro %}

namespace SP
{
	{{gen_procedures() | indent}}
};