{%- macro upper_first(text) %}{{text[0]|upper}}{{text[1:]}}{% endmacro -%}

{%- for proc in procs %}
class Names
{
public:
	class roles
	{
	public:
	{%- for role in proc.roles %}
		const std::wstring _{{role.name}} = L"{{role.name}}";
	{%- endfor %}
	} roles;

	class
	{
	public:
	{%- for category in proc.categories %}
		class
		{
		public:
			const std::wstring _name = L"{{category.name}}";
		{%- for channel in category.channels %}
			const std::wstring _{{channel.name}} = L"{{channel.name}}";
		{%- endfor %}
		} {{category.name}};
	{%- endfor %}
	} categories;


};
{% endfor %}