#pragma once
#include "Types.h"
#include <Windows.h>

namespace dnc
{
	
    class Names
    {
    public:
    	class roles
    	{
    	public:
    		const std::wstring _adventurer = L"adventurer";
    		const std::wstring _test = L"test";
    	} roles;

    	class
    	{
    	public:
    		class
    		{
    		public:
    			const std::wstring _name = L"pier";
    			const std::wstring _reg = L"reg";
    		} pier;
    		class
    		{
    		public:
    			const std::wstring _name = L"bigeumdo";
    			const std::wstring _announcement = L"announcement";
    			const std::wstring _roles = L"roles";
    		} bigeumdo;
    		class
    		{
    		public:
    			const std::wstring _name = L"myinfo";
    			const std::wstring _mailbox = L"mailbox";
    			const std::wstring _office = L"office";
    		} myinfo;
    		class
    		{
    		public:
    			const std::wstring _name = L"square";
    			const std::wstring _chat = L"chat";
    		} square;
    	} categories;


    };
     
};