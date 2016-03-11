  /// \file DQMXmlHelper.h
/*
 *
 * DQMXmlHelper.h header template automatically generated by a class generator
 * Creation date : mar. juil. 1 2014
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


#ifndef DQMXMLHELPER_H
#define DQMXMLHELPER_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"
#include "dqm4hep/tinyxml.h"
#include "dqm4hep/DQMLogging.h"

namespace dqm4hep
{

class DQMModule;

/** DQMXmlHelper class
 */
class DQMXmlHelper
{
public:
	/** Read a value from an xml element
	 */
	template <typename T>
	static StatusCode readValue(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, T &t);

	/** Read a vector of values from a (space separated) list in an xml element
	 */
	template <typename T>
	static StatusCode readVectorOfValues(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, std::vector<T> &vector);

	/** Read a two-dimensional array of values into a vector of vectors. Each row of values must be contained
	 *          within <rowname></rowname> xml tags, whilst the values in the row must be space separated
	 */
	template <typename T>
	static StatusCode read2DVectorOfValues(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, const std::string &rowName,
					std::vector< std::vector<T> > &vector);

	/** Get the attribute of the xml element
	 */
	template <typename T>
	static StatusCode getAttribute(const TiXmlElement *const pXmlElement, const std::string &attributeName, T &attributeValue);

	/** Get the attribute of the xml element and use a validator to validate the value
	 */
	template <typename T, typename Validator>
	static StatusCode getAttribute(const TiXmlElement *const pXmlElement, const std::string &attributeName, T &attributeValue, Validator validator);

	/** Read a parameter value from an xml element
	 */
	template <typename T>
	static StatusCode readParameterValue(const TiXmlHandle &xmlHandle, const std::string &parameterName, T &t);

	/** Read a vector of values for a parameter from a (space separated) list in an xml element
	 */
	template <typename T>
	static StatusCode readParameterValues(const TiXmlHandle &xmlHandle, const std::string &parameterName, std::vector<T> &vector);

	/** Create a quality test. Works if the quality test factory has been registered first
	 */
	static StatusCode createQualityTest(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &qualityTestName);

	/** Create a monitor element from a xml handle
	 */
	static StatusCode bookMonitorElement(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &meStringId,
			DQMMonitorElement *&pMonitorElement);

	/** Create a monitor element from a xml handle
	 */
	static StatusCode bookMonitorElement(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &meStringId,
			const std::string &strSuffix, DQMMonitorElement *&pMonitorElement);

	/** Create a monitor element from a xml handle
	 */
	static StatusCode bookMonitorElement(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &meStringId,
			unsigned int suffix, DQMMonitorElement *&pMonitorElement);

	/** Tokenize a string
	 */
	static void tokenizeString(const std::string &inputString, StringVector &tokens, const std::string &delimiter = " ");
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template <typename T>
inline StatusCode DQMXmlHelper::readValue(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, T &t)
{
    const TiXmlElement *const pXmlElement = xmlHandle.FirstChild(xmlElementName).Element();

    if (NULL == pXmlElement)
        return STATUS_CODE_NOT_FOUND;

    if (!DQM4HEP::stringToType(pXmlElement->GetText(), t))
        return STATUS_CODE_FAILURE;

    return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <>
inline StatusCode DQMXmlHelper::readValue<bool>(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, bool &t)
{
    const TiXmlElement *const pXmlElement = xmlHandle.FirstChild(xmlElementName).Element();

    if (NULL == pXmlElement)
        return STATUS_CODE_NOT_FOUND;

    const std::string xmlElementString = pXmlElement->GetText();

    if ((xmlElementString == "1") || (xmlElementString == "true"))
    {
        t = true;
    }
    else if ((xmlElementString == "0") || (xmlElementString == "false"))
    {
        t = false;
    }
    else
    {
        return STATUS_CODE_FAILURE;
    }

    return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline StatusCode DQMXmlHelper::readVectorOfValues(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, std::vector<T> &vector)
{
    const TiXmlElement *const pXmlElement = xmlHandle.FirstChild(xmlElementName).Element();

    if (NULL == pXmlElement)
        return STATUS_CODE_NOT_FOUND;

    StringVector tokens;
    tokenizeString(pXmlElement->GetText(), tokens);

    for (StringVector::const_iterator iter = tokens.begin(), iterEnd = tokens.end(); iter != iterEnd; ++iter)
    {
        T t;

        if (!DQM4HEP::stringToType(*iter, t))
            return STATUS_CODE_FAILURE;

        vector.push_back(t);
    }

    return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline StatusCode DQMXmlHelper::read2DVectorOfValues(const TiXmlHandle &xmlHandle, const std::string &xmlElementName, const std::string &rowName,
    std::vector< std::vector<T> > &vector)
{
    TiXmlElement *pXmlElement = xmlHandle.FirstChild(xmlElementName).Element();

    if (NULL == pXmlElement)
        return STATUS_CODE_NOT_FOUND;

    TiXmlElement *pXmlRowElement = TiXmlHandle(pXmlElement).FirstChild(rowName).Element();

    if (NULL == pXmlRowElement)
        return STATUS_CODE_NOT_FOUND;

    for ( ; NULL != pXmlRowElement; pXmlRowElement = pXmlRowElement->NextSiblingElement(rowName))
    {
        std::vector<T> rowVector;

        StringVector tokens;
        tokenizeString(pXmlRowElement->GetText(), tokens);

        for (StringVector::const_iterator iter = tokens.begin(), iterEnd = tokens.end(); iter != iterEnd; ++iter)
        {
            T t;

            if (!DQM4HEP::stringToType(*iter, t))
                return STATUS_CODE_FAILURE;

            rowVector.push_back(t);
        }

        vector.push_back(rowVector);
    }

    return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline StatusCode DQMXmlHelper::getAttribute(const TiXmlElement *const pXmlElement, const std::string &attributeName, T &attributeValue)
{
	if(NULL == pXmlElement)
		return STATUS_CODE_INVALID_PTR;

	const char *pAttributePtr(pXmlElement->Attribute(attributeName.c_str()));

	if(NULL == pAttributePtr)
		return STATUS_CODE_NOT_FOUND;

	std::string attributeStr(pAttributePtr);

	if(!DQM4HEP::stringToType(attributeStr, attributeValue))
		return STATUS_CODE_FAILURE;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <typename T, typename Validator>
inline StatusCode DQMXmlHelper::getAttribute(const TiXmlElement *const pXmlElement, const std::string &attributeName, T &attributeValue, Validator validator)
{
	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute<T>(pXmlElement, attributeName, attributeValue));

	if(!validator(attributeValue))
		return STATUS_CODE_INVALID_PARAMETER;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <>
inline StatusCode DQMXmlHelper::getAttribute(const TiXmlElement *const pXmlElement, const std::string &attributeName, std::string &attributeValue)
{
	if(NULL == pXmlElement)
		return STATUS_CODE_INVALID_PTR;

	const char *pAttributePtr(pXmlElement->Attribute(attributeName.c_str()));

	if(NULL == pAttributePtr)
		return STATUS_CODE_NOT_FOUND;

	attributeValue = pAttributePtr;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline StatusCode DQMXmlHelper::readParameterValue(const TiXmlHandle &xmlHandle, const std::string &parameterName, T &t)
{
    for (TiXmlElement *pXmlElement = xmlHandle.FirstChild("parameter").Element(); NULL != pXmlElement;
        pXmlElement = pXmlElement->NextSiblingElement("parameter"))
    {
    	std::string name;
    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "name", name));

    	if(name != parameterName)
    		continue;

        if (!DQM4HEP::stringToType(pXmlElement->GetText(), t))
            return STATUS_CODE_FAILURE;

        return STATUS_CODE_SUCCESS;
    }

    return STATUS_CODE_NOT_FOUND;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline StatusCode DQMXmlHelper::readParameterValues(const TiXmlHandle &xmlHandle, const std::string &parameterName, std::vector<T> &vector)
{
    for (TiXmlElement *pXmlElement = xmlHandle.FirstChild("parameter").Element(); NULL != pXmlElement;
        pXmlElement = pXmlElement->NextSiblingElement("parameter"))
    {
    	std::string name;
    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "name", name));

    	if(name != parameterName)
    		continue;

        StringVector tokens;
        tokenizeString(pXmlElement->GetText(), tokens);

        for (StringVector::const_iterator iter = tokens.begin(), iterEnd = tokens.end(); iter != iterEnd; ++iter)
        {
            T t;

            if (!DQM4HEP::stringToType(*iter, t))
                return STATUS_CODE_FAILURE;

            vector.push_back(t);
        }

        return STATUS_CODE_SUCCESS;
    }

    return STATUS_CODE_NOT_FOUND;
}

}

#endif //  XMLHELPER_H
