#include <client/crash_report_database.h>
#include <client/settings.h>
#include <client/crashpad_client.h>
#include <fstream>
#include <string>
#include <array>
#include "version_info.h"

#if defined __has_attribute
#  if __has_attribute (init_priority)
#    define INITPRIO_CLASS __attribute__ ((init_priority (100)))
#  endif
#endif

#ifndef INITPRIO_CLASS
#   ifdef _MSC_VER
#pragma init_seg(lib)
#   endif
#endif

#ifndef INITPRIO_CLASS
#   define INITPRIO_CLASS
#endif

class crash_reporter
{
	crashpad::CrashpadClient client;

public:
	crash_reporter();
}

crash_reporter::crash_reporter()
{
	crashpad::base::FilePath db("crashdumps");
	crashpad::base::FilePath handler("crashpad_handler.exe");

	std::map<std::string, std::string> annotations;
	annotations["git_hash"] = GIT_HASH;
	annotations["src_date"] = SRC_DATE;
	annotations["format"] = "minidump";
	annotations["token"] = "970bc3e28c3fe82a2d772b2af9fabe3b40ec6dcf9dd505209254abb0657b54fe";

	std::vector<std::string> arguments;
	arguments.push_back("--no-rate-limit");

	std::unique_ptr<crashpad::CrashReportDatabase> database = crashpad::CrashReportDatabase::Initialize(reportsDir);

	if (database == nullptr || database->GetSettings() == NULL)
		return false;
	database->GetSettings()->SetUploadsEnabled(true);

	std::string url("https://submit.backtrace.io/eu07/970bc3e28c3fe82a2d772b2af9fabe3b40ec6dcf9dd505209254abb0657b54fe/minidump");

	if (!client.StartHandler(handler, db, db, url, annotations, arguments, true, true))
		return;

	client.WaitForHandlerStart(crashpad::INFINITE);
}

crash_reporter crash_reporter_inst INITPRIO_CLASS;

void crashreport_add_info(const char *name, const std::string &value)
{
	char *copy = new char[value.size() + 1];
	strcpy(copy, value.c_str());

	crashpad::Annotation *annotation = new crashpad::Annotation(crashpad::Annotation::Type::kString, name, copy);
	annotation->SetSize(value.size() + 1);
}
