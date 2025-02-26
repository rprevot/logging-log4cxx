/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <log4cxx/logstring.h>
#include <log4cxx/level.h>
#include <log4cxx/helpers/stringhelper.h>
#include <log4cxx/helpers/transcoder.h>
#if !defined(LOG4CXX)
	#define LOG4CXX 1
#endif
#include <log4cxx/helpers/aprinitializer.h>
#include <mutex>

using namespace LOG4CXX_NS;
using namespace LOG4CXX_NS::helpers;

IMPLEMENT_LOG4CXX_OBJECT_WITH_CUSTOM_CLASS(Level, LevelClass)

LevelPtr Level::getOff()
{
	static WideLife<LevelPtr> offLevel = std::make_shared<Level>(Level::OFF_INT, LOG4CXX_STR("OFF"), 0);
	return offLevel;
}

LevelPtr Level::getFatal()
{
	static WideLife<LevelPtr> fatalLevel = std::make_shared<Level>(Level::FATAL_INT, LOG4CXX_STR("FATAL"), 0);
	return fatalLevel;
}

LevelPtr Level::getError()
{
	static WideLife<LevelPtr> errorLevel = std::make_shared<Level>(Level::ERROR_INT, LOG4CXX_STR("ERROR"), 3);
	return errorLevel;
}

LevelPtr Level::getWarn()
{
	static WideLife<LevelPtr> warnLevel = std::make_shared<Level>(Level::WARN_INT, LOG4CXX_STR("WARN"), 4);
	return warnLevel;
}

LevelPtr Level::getInfo()
{
	static WideLife<LevelPtr> infoLevel = std::make_shared<Level>(Level::INFO_INT, LOG4CXX_STR("INFO"), 6);
	return infoLevel;
}

LevelPtr Level::getDebug()
{
	static WideLife<LevelPtr> debugLevel = std::make_shared<Level>(Level::DEBUG_INT, LOG4CXX_STR("DEBUG"), 7);
	return debugLevel;
}

LevelPtr Level::getTrace()
{
	static WideLife<LevelPtr> traceLevel = std::make_shared<Level>(Level::TRACE_INT, LOG4CXX_STR("TRACE"), 7);
	return traceLevel;
}


LevelPtr Level::getAll()
{
	static WideLife<LevelPtr> allLevel = std::make_shared<Level>(Level::ALL_INT, LOG4CXX_STR("ALL"), 7);
	return allLevel;
}



Level::Level(int level1,
	const LogString& name1, int syslogEquivalent1)
	: level(level1), name(name1), syslogEquivalent(syslogEquivalent1)
{
	APRInitializer::initialize();
}


LevelPtr Level::toLevelLS(const LogString& sArg)
{
	return toLevelLS(sArg, Level::getDebug());
}

LogString Level::toString() const
{
	return name;
}


LevelPtr Level::toLevel(int val)
{
	return toLevel(val, Level::getDebug());
}

LevelPtr Level::toLevel(int val, const LevelPtr& defaultLevel)
{
	switch (val)
	{
		case ALL_INT:
			return getAll();

		case DEBUG_INT:
			return getDebug();

		case TRACE_INT:
			return getTrace();

		case INFO_INT:
			return getInfo();

		case WARN_INT:
			return getWarn();

		case ERROR_INT:
			return getError();

		case FATAL_INT:
			return getFatal();

		case OFF_INT:
			return getOff();

		default:
			return defaultLevel;
	}
}

LevelPtr Level::toLevel(const std::string& sArg)
{
	return toLevel(sArg, Level::getDebug());
}

LevelPtr Level::toLevel(const std::string& sArg, const LevelPtr& defaultLevel)
{
	LOG4CXX_DECODE_CHAR(s, sArg);
	return toLevelLS(s, defaultLevel);
}

void Level::toString(std::string& dst) const
{
	Transcoder::encode(name, dst);
}

#if LOG4CXX_WCHAR_T_API
LevelPtr Level::toLevel(const std::wstring& sArg)
{
	return toLevel(sArg, Level::getDebug());
}

LevelPtr Level::toLevel(const std::wstring& sArg, const LevelPtr& defaultLevel)
{
	LOG4CXX_DECODE_WCHAR(s, sArg);
	return toLevelLS(s, defaultLevel);
}

void Level::toString(std::wstring& dst) const
{
	Transcoder::encode(name, dst);
}

#endif

#if LOG4CXX_UNICHAR_API || LOG4CXX_LOGCHAR_IS_UNICHAR
LevelPtr Level::toLevel(const std::basic_string<UniChar>& sArg)
{
	return toLevel(sArg, Level::getDebug());
}

LevelPtr Level::toLevel(const std::basic_string<UniChar>& sArg, const LevelPtr& defaultLevel)
{
	LOG4CXX_DECODE_UNICHAR(s, sArg);
	return toLevelLS(s, defaultLevel);
}

void Level::toString(std::basic_string<UniChar>& dst) const
{
	Transcoder::encode(name, dst);
}

#endif

#if LOG4CXX_CFSTRING_API
LevelPtr Level::toLevel(const CFStringRef& sArg)
{
	return toLevel(sArg, Level::getDebug());
}

LevelPtr Level::toLevel(const CFStringRef& sArg, const LevelPtr& defaultLevel)
{
	LogString s;
	Transcoder::decode(sArg, s);
	return toLevelLS(s, defaultLevel);
}

void Level::toString(CFStringRef& dst) const
{
	dst = Transcoder::encode(name);
}
#endif


LevelPtr Level::toLevelLS(const LogString& sArg, const LevelPtr& defaultLevel)
{
	const LogString trimmed(StringHelper::trim(sArg));
	const size_t len = trimmed.length();

	if (len == 4)
	{
		if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("INFO"), LOG4CXX_STR("info")))
		{
			return getInfo();
		}

		if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("WARN"), LOG4CXX_STR("warn")))
		{
			return getWarn();
		}
	}
	else
	{
		if (len == 5)
		{
			if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("DEBUG"), LOG4CXX_STR("debug")))
			{
				return getDebug();
			}

			if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("TRACE"), LOG4CXX_STR("trace")))
			{
				return getTrace();
			}

			if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("ERROR"), LOG4CXX_STR("error")))
			{
				return getError();
			}

			if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("FATAL"), LOG4CXX_STR("fatal")))
			{
				return getFatal();
			}
		}
		else
		{
			if (len == 3)
			{
				if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("OFF"), LOG4CXX_STR("off")))
				{
					return getOff();
				}

				if (StringHelper::equalsIgnoreCase(trimmed, LOG4CXX_STR("ALL"), LOG4CXX_STR("all")))
				{
					return getAll();
				}
			}
		}
	}

	return defaultLevel;
}


bool Level::equals(const LevelPtr& level1) const
{
	return level1 && this->level == level1->level;
}

bool Level::isGreaterOrEqual(const LevelPtr& level1) const
{
	return level1 && this->level >= level1->level;
}

