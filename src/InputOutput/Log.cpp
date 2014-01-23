/*
 *  This file is part of AQUAgpusph, a free CFD program based on SPH.
 *  Copyright (C) 2012  Jose Luis Cercos Pita <jl.cercos@upm.es>
 *
 *  AQUAgpusph is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AQUAgpusph is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with AQUAgpusph.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

#include <InputOutput/Log.h>
#include <ScreenManager.h>
#include <CalcServer.h>
#include <AuxiliarMethods.h>

namespace Aqua{ namespace InputOutput{

Log::Log()
    : _file(NULL)
{
    if(create())
        exit(EXIT_FAILURE);
}

Log::~Log()
{
    close();
}

bool Log::save(){
    if(!_file){
        return true;
    }

    return false;
}

bool Log::create(){
    char msg[1024];
	ScreenManager *S = ScreenManager::singleton();

    if(file("log.%d.html")){
        S->addMessageF(3, "Failure getting a valid filename.\n");
        S->addMessageF(0, "\tHow do you received this message?.\n");
        return true;
    }
    _file = fopen(file());
    if(!_file){
        sprintf(msg,
                "Failure creating the log file \"%s\"\n",
                file());
        return true;
    }

	fprintf(_file, "<html>\n");
	fprintf(_file, "<head><title>AQUAgpusph log file.</title></head>\n");
	fprintf(_file, "<body bgcolor=\"#f0ffff\">\n");
	fprintf(_file, "<h1 align=\"center\">AQUAgpusph log file.</h1>\n");
	// Starting data
	struct timeval now_time;
	gettimeofday(&now_time, NULL);
	const time_t seconds = now_time.tv_sec;
	fprintf(_file, "<p align=\"left\">%s</p>\n", ctime(&seconds));
	fprintf(_file, "<hr><br>\n");
	fflush(_file);

	return false;
}

bool Log::close(){
    if(!_file)
        return true;

	unsigned int i;
	char msg[512];
	ScreenManager *S = ScreenManager::singleton();
	CalcServer::CalcServer *C = CalcServer::CalcServer::singleton();
	float fluid_mass = 0.f;
	int *imove = new int[C->N];
	float *mass = new float[C->N];
	int err_code = CL_SUCCESS;
	strcpy(msg, "");
	// Compute fluid mass if possible
	err_code |= C->getData(imove, C->imove, C->N * sizeof( int ));
	err_code |= C->getData(mass, C->mass, C->N * sizeof( float ));
	if(err_code == CL_SUCCESS){
        for(i=0;i<C->N;i++) {
            if(imove[i] > 0)
                fluid_mass += mass[i];
        }
        delete[] imove; imove=0;
        delete[] mass; mass=0;
        sprintf(msg,
                "Lost mass = %g [kg] (from %g [kg])\n",
                C->fluid_mass - fluid_mass,
                C->fluid_mass);
        S->addMessageF(1, msg);

	}

	fprintf(_log_file_id, "<br><hr>\n");
	struct timeval now_time;
	gettimeofday(&now_time, NULL);
	const time_t seconds = now_time.tv_sec;
	fprintf(_log_file_id,
            "<b><font color=\"#000000\">End of simulation</font></b><br>\n");
	fprintf(_log_file_id, "<p align=\"left\">%s</p>\n", ctime(&seconds));
	fprintf(_log_file_id, "</body>\n");
	fprintf(_log_file_id, "</html>\n");

	fflush(_file);
    fclose(_file);
    _file = NULL;

	return false;
}

}}  // namespace
