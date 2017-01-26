  /// \file JsonConfigurationIO.cc
/*
 *
 * JsonConfigurationIO.cc source template automatically generated by a class generator
 * Creation date : jeu. janv. 26 2017
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


#include "dqm4hep/JsonConfigurationIO.h"
#include "dqm4hep/ConfigurationHandle.h"
#include "dqm4hep/Logging.h"

#include <fstream>

namespace dqm4hep {

  namespace core {


    StatusCode JsonConfigurationIO::read(const std::string &jsonFileName, ParameterDirectory *pDirectory)
    {
      // Parse the file
      Json::Reader reader;
      std::ifstream ifs (jsonFileName.c_str(), std::ifstream::in);

      // Let's parse it
      Json::Value rootValue;
      bool parsedSuccess = reader.parse(ifs, rootValue, false);

      if(!parsedSuccess)
      {
        LOG4CXX_FATAL( dqmMainLogger, "JsonConfigurationIO::read(): Failed to parse json file : " + reader.getFormatedErrorMessages() );

        return STATUS_CODE_FAILURE;
      }

      return this->read(rootValue, pDirectory);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode JsonConfigurationIO::write(const std::string &jsonFileName, ParameterDirectory *pDirectory)
    {
      Json::Value rootValue;
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->write(rootValue, pDirectory->createHandle()));

      Json::StyledWriter writer;
      std::ofstream ofs (jsonFileName.c_str(), std::ofstream::out);
      ofs << writer.write(rootValue);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    std::string JsonConfigurationIO::getType() const
    {
      return "json";
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode JsonConfigurationIO::read(const Json::Value &value, ParameterDirectory *pDirectory)
    {
      StringVector keys(value.getMemberNames());

      for(auto iter = keys.begin(), endIter = keys.end() ; endIter != iter ; ++iter)
      {
        Json::Value member(value[*iter]);

        if(*iter == "parameters")
        {
          StringVector parameterKeys(member.getMemberNames());

          for(auto jter = parameterKeys.begin(), endJter = parameterKeys.end() ; endJter != jter ; ++jter)
          {
            std::string value(member[*jter].asString());
            pDirectory->getParameters().set(*jter, value);
          }
        }
        else
        {
          ParameterDirectory *pSubDirectory = pDirectory->mkdir(*iter);

          if(nullptr == pSubDirectory)
            return STATUS_CODE_FAILURE;

          this->read(member, pSubDirectory);
        }
      }

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode JsonConfigurationIO::write(Json::Value &value, const ConfigurationHandle &configHandle)
    {
      StringVector directoryList(configHandle.getSubDirectorList());

      for(auto iter = directoryList.begin(), endIter = directoryList.end() ; endIter != iter ; ++iter)
      {
        ConfigurationHandle subConfigHandle(configHandle.createHandle(*iter));
        Json::Value subDirValue;

        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->write(subDirValue, subConfigHandle));
        value[*iter] = subDirValue;
      }

      StringVector parameterNames(configHandle.getParameterNames());
      Json::Value parametersValue;

      for(auto iter = parameterNames.begin(), endIter = parameterNames.end() ; endIter != iter ; ++iter)
      {
        StringParameter parameter;
        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, configHandle.getParameter(*iter, parameter));

        parametersValue[*iter] = parameter.get();
      }

      value["parameters"] = parametersValue;

      return STATUS_CODE_SUCCESS;
    }

  }

}