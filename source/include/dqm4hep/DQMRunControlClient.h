  /// \file DQMRunControlClient.h
/*
 *
 * DQMRunControlClient.h header template automatically generated by a class generator
 * Creation date : mer. nov. 12 2014
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMRUNCONTROLCLIENT_H
#define DQMRUNCONTROLCLIENT_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"
#include "dqm4hep/DQMRunControl.h"

// -- dim headers
#include "dic.hxx"

namespace dqm4hep
{

class DQMRun;

/** DQMRunControlClient interface
 */ 
class DQMRunControlClient : public DQMRunControl
{
public:
	/** Constructor
	 */
	DQMRunControlClient() : DQMRunControl () {}

	/** Destructor
	 */
	virtual ~DQMRunControlClient() {}

	/** Connect to the service.
	 */
	virtual StatusCode connectToService() = 0;

	/** Disconnect from the service
	 */
	virtual StatusCode disconnectFromService() = 0;

	/** Whether the client is connected to the service
	 */
	virtual bool isConnectedToService() const = 0;
}; 

} 

#endif  //  DQMRUNCONTROLCLIENT_H
