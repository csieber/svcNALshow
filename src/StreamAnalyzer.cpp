/*
 * This file is part of the SVC multi-path streaming project.
 *
 * Chair of Communication Networks, Department of Computer
 * Science at Julius-Maximilians University of Wuerzburg.
 *
 *
 * Contact:
 * Christian Sieber <sieber@informatik.uni-wuerzburg.de>
 * Thomas Zinner <zinner@informatik.uni-wuerzburg.de>
 */

#include <iostream>
#include <boost/program_options.hpp>
#include "common/h264Decoder/h264Decoder.h"
#include "common/h264Decoder/h264StreamDb.h"
#include "common/h264Decoder/h264StreamStats.h"
#include "common/h264Decoder/NALStreams/NALFileStream.h"

int main(int argc, char** argv) {

	/*
	 * Read command line options.
	 */

	namespace po = boost::program_options;

	po::options_description desc("Options");
	desc.add_options()
	    ("help", "Help")
	    ("file,F", po::value<std::string>()->required(), "SVC stream");

	po::variables_map vm;

	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	}
	catch (boost::program_options::required_option& ex) {

		std::cerr << "Required option '" << ex.get_option_name()
				  << "' is missing!" << std::endl << std::endl
				  << desc << std::endl;

		return 1;
	}
	catch (boost::program_options::invalid_option_value& ex) {

		std::cerr << "Option '" << ex.get_option_name()
				  << "' has an invalid value!" << std::endl << std::endl
				  << desc << std::endl;

		return 1;
	}
	catch (boost::program_options::unknown_option& ex) {

		std::cerr << "Unknown option '" << ex.get_option_name()
				  << "'!" << std::endl << std::endl
				  << desc << std::endl;

		return 1;
	}
	catch (boost::program_options::invalid_command_line_syntax& ex) {

		std::cerr << "Invalid syntax! What(): '" << ex.what() << std::endl << std::endl
				  << desc << std::endl;

		return 1;
	}

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    return 1;
	}

	std::string svc_file = vm["file"].as<std::string>();

	/*
	 * Read SVC file
	 */
	using H264::NALFileStream;
	using H264::h264Decoder;
	using H264::h264StreamDb;
	using H264::h264StreamStats;
	using H264::nal_short_info;

	NALFileStream* stream = new NALFileStream();

	if (!stream->open(svc_file)) {

		std::cerr << "h264: Failed to open " << svc_file << ". Exiting!" << std::endl;
		return false;
	}

	if (!stream->loadIndex()) {

		std::cout << "h264: file index missing. Creating new one. This might take a while." << std::endl;

		if (!stream->createIndex()) {

			std::cerr << "h264: Failed to create index! Exiting!" << std::endl;
			return false;
		}

		if (!stream->saveIndex()) {

			std::cerr << "h264: Failed to save index! Please check your file or folder permissions. Exiting" << std::endl;
			return false;
		}
	}

	// Decode the SVC file.
	H264::h264Decoder::ptr decoder = h264Decoder::ptr(new h264Decoder(stream));;
	H264::h264StreamDb::ptr streamdb = h264StreamDb::ptr(new h264StreamDb());;
	H264::h264StreamStats::ptr streamstats = h264StreamStats::ptr(new h264StreamStats());

	bool create[2] = {false, false};

	if (!streamdb->load(svc_file + ".db")) {

		std::cout << "h264: No stream database found. Creating a new one. This might take a while." << std::endl;
		create[0] = true;
	}

	if (!streamstats->load(svc_file + ".stats")) {

		std::cout << "h264: No stream statistics found. Creating new statistics. This might take a while." << std::endl;
		create[1] = true;
	}

	if (!create[0] && !create[1]) {

		std::cout << "h264: Index, Database, Statistics: OKAY " << std::endl;
		return true;
	}

	nal_short_info nal = decoder->next();
	float perc = 0;

	while (nal.pNal.get<1>() != -1) {

		if (stream->posNal() % 300 == 0) {

			perc = (float)stream->posNal()/(float)stream->nalIndexSize()*100;
			std::cout << "Progress: " << perc << "%" << std::endl;
		}

		if (create[0])
			*streamdb << nal;

		if (create[1])
			*streamstats << nal;

		nal = decoder->next();
	}

	if (create[0]) {

		// It is not mandatory to save the database,
		// but we want to enforce it here.
		if (!streamdb->save(svc_file + ".db")) {

			std::cerr << "h264: Failed to save stream database! Check file permissions. Exiting." << std::endl;
			return false;
		}
	}

	if (create[1]) {

		// It is not mandatory to save the statistics,
		// but we want to enforce it here.
		if (!streamstats->save(svc_file + ".stats")) {

			std::cerr << "h264: Failed to save stream statistics! Check file permissions. Exiting." << std::endl;
			return false;
		}
	}

	std::cout << "h264: Finished creating database/statistics." << std::endl;

	return 0;
}
