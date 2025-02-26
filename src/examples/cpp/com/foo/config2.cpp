#include "com/foo/config.h"
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/logmanager.h>

namespace com { namespace foo {

auto getLogger(const std::string& name) -> LoggerPtr {
	static struct log4cxx_initializer {
		log4cxx_initializer() {
			if (log4cxx::PropertyConfigurator::configure("MyApp.properties") == log4cxx::spi::ConfigurationStatus::NotConfigured)
				log4cxx::BasicConfigurator::configure(); // Send events to the console
		}
		~log4cxx_initializer() {
			log4cxx::LogManager::shutdown();
		}
	} initAndShutdown;
	return name.empty()
		? log4cxx::LogManager::getRootLogger()
		: log4cxx::LogManager::getLogger(name);
}

} } // namespace com::foo
