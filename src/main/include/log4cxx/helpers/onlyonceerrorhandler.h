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

#ifndef _LOG4CXX_HELPERS_ONLY_ONCE_ERROR_HANDLER_H
#define _LOG4CXX_HELPERS_ONLY_ONCE_ERROR_HANDLER_H

#include <log4cxx/spi/errorhandler.h>
#include <log4cxx/helpers/object.h>

namespace LOG4CXX_NS
{
namespace helpers
{
/**
The <code>OnlyOnceErrorHandler</code> implements log4cxx's default
error handling policy which consists of emitting a message for the
first error in an appender and ignoring all following errors.

<p>The error message is printed on <code>System.err</code>.

<p>This policy aims at protecting an otherwise working application
from being flooded with error messages when logging fails
*/
class LOG4CXX_EXPORT OnlyOnceErrorHandler :
	public virtual spi::ErrorHandler,
	public virtual Object
{
	private:
		LOG4CXX_DECLARE_PRIVATE_MEMBER_PTR(OnlyOnceErrorHandlerPrivate, m_priv)

	public:
		DECLARE_LOG4CXX_OBJECT(OnlyOnceErrorHandler)
		BEGIN_LOG4CXX_CAST_MAP()
		LOG4CXX_CAST_ENTRY(spi::OptionHandler)
		LOG4CXX_CAST_ENTRY(spi::ErrorHandler)
		END_LOG4CXX_CAST_MAP()

		OnlyOnceErrorHandler();

		~OnlyOnceErrorHandler();

		/**
		 Does not do anything.
		 */
		void setLogger(const LoggerPtr& logger) override;


		/**
		\copybrief spi::OptionHandler::activateOptions()

		No action is performed in this implementation.
		*/
		void activateOptions(helpers::Pool& p) override;

		/**
		\copybrief spi::OptionHandler::setOption()

		Supported options | Supported values | Default value
		-------------- | ---------------- | ---------------
		- | - | -
		*/
		void setOption(const LogString& option, const LogString& value) override;


		/**
		Prints the message and the stack trace of the exception on
		<code>System.err</code>.  */
		void error(const LogString& message, const std::exception& e,
			int errorCode) const override;
		/**
		Prints the message and the stack trace of the exception on
		<code>System.err</code>.
		*/
		void error(const LogString& message, const std::exception& e,
			int errorCode, const spi::LoggingEventPtr& event) const override;

		/**
		Print a the error message passed as parameter on
		<code>System.err</code>.
		*/
		void error(const LogString& message) const override;

		/**
		Does not do anything.
		*/
		void setAppender(const AppenderPtr& appender) override;

		/**
		Does not do anything.
		*/
		void setBackupAppender(const AppenderPtr& appender) override;
};
}  // namespace helpers
} // namespace log4cxx

#endif //_LOG4CXX_HELPERS_ONLY_ONCE_ERROR_HANDLER_H

