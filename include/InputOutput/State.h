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

#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <InputOutput/InputOutput.h>

namespace Aqua{
namespace InputOutput{

/** \class State State.h InputOutput/State.h
 *  Load/Save the XML simulation definition.
 */
class State : public InputOutput
{
public:
	/** Constructor
	 */
	State();

	/** Destructor
	 */
	~State();

    /** Save the data
     * @return false if all gone right, true otherwise.
     */
    bool save();

    /** Load the data
     * @return false if all gone right, true otherwise.
     */
    bool load();

private:
    /** Parse the XML file
	 * @param filepath file to be parsed.
	 * @return false if all gone right, true otherwise
     */
    bool parse(const char* filepath);

	/** Look for general settings sections.
	 * @param root root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseSettings(xercesc::DOMElement *root);

	/** Look for variables sections.
	 * @param root root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseVariables(xercesc::DOMElement *root);

	/** Look for tools sections.
	 * @param root root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseTools(xercesc::DOMElement *root);

	/** Look for OpenCL settings sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseOpenCL(xercesc::DOMElement *root);

	/** Look for time control sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseTiming(xercesc::DOMElement *root);

	/** Look for SPH settings sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseSPH(xercesc::DOMElement *root);

	/** Look for fluids sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseFluid(xercesc::DOMElement *root);

	/** Look for particles set sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseSet(xercesc::DOMElement *root);

	/** Look for sensors sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseSensors(xercesc::DOMElement *root);

	/** Look for movements sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseMotions(xercesc::DOMElement *root);

	/** Look for portals sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parsePortals(xercesc::DOMElement *root);

	/** Look for ghost particles sections.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool parseGhostParticles(xercesc::DOMElement *root);

    /** Write the XML file
	 * @param filepath file to be written.
	 * @return false if all gone right, true otherwise
     */
    bool write(const char* filepath);

	/** Write the settings section.
	 * @param doc XML generated document.
	 * @param root root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeSettings(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the variables section.
	 * @param doc XML generated document.
	 * @param root root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeVariables(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the tools section.
	 * @param doc XML generated document.
	 * @param root root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeTools(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Wrute the OpenCL section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeOpenCL(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the time control section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeTiming(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the SPH settings section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeSPH(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the fluids sections.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeFluid(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the particles set sections.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeSet(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the sensors section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeSensors(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the movements section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeMotions(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** write the portals section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writePortals(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

	/** Write the ghost particles section.
	 * @param doc XML generated document.
	 * @param root Root XML node.
	 * @return false if all gone right, true otherwise
	 */
	bool writeGhostParticles(xercesc::DOMDocument* doc, xercesc::DOMElement *root);

    /// Output file
    char* _output_file;
};  // class InputOutput

}}  // namespaces

#endif // STATE_H_INCLUDED
