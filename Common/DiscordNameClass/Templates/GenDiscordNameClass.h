#pragma once
#include "Types.h"
#include <Windows.h>

{%- macro gen_discordnameclass() -%} {% include 'DiscordNameClass.h' %} {% endmacro %}

namespace dnc
{
	{{gen_discordnameclass() | indent}}
};