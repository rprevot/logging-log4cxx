/*
 * Copyright 1999,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 #include <log4cxx/pattern/filelocationpatternconverter.h>
 #include <log4cxx/spi/loggingevent.h>
 #include <log4cxx/spi/location/locationinfo.h>

 using namespace log4cxx;
 using namespace log4cxx::pattern;
 using namespace log4cxx::spi;
 using namespace helpers;

IMPLEMENT_LOG4CXX_OBJECT(FileLocationPatternConverter)

FileLocationPatternConverter::FileLocationPatternConverter() :
    LoggingEventPatternConverter(LOG4CXX_STR("File Location"),
       LOG4CXX_STR("file")) {
}

PatternConverterPtr FileLocationPatternConverter::newInstance(
    const std::vector<LogString>& options) {
    static PatternConverterPtr instance(new FileLocationPatternConverter());
    return instance;
}

void FileLocationPatternConverter::format(
   const LoggingEventPtr& event,
   LogString& toAppendTo,
   Pool& p) const {
    append(toAppendTo, event->getLocationInformation().getFileName());
}