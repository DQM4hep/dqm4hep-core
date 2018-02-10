/// \file QualityTest.h
/*
 *
 * QualityTest.h header template automatically generated by a class generator
 * Creation date : ven. f�vr. 20 2015
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
 * @author Remi Ete, DESY
 */

#ifndef DQM4HEP_QUALITYTEST_H
#define DQM4HEP_QUALITYTEST_H

// -- dqm4hep headers
#include <dqm4hep/Internal.h>
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/json.h>

// -- root headers
#include <TObject.h>

namespace dqm4hep {

  namespace core {

    class TiXmlHandle;
    
    enum QualityFlag {
      UNDEFINED,
      INVALID,
      INSUFFICENT_STAT,
      SUCCESS,
      WARNING,
      ERROR
    };

    /** QualityTestReport class
     *  Hanlde the result of a quality test
     */
    class QualityTestReport {
    public:
      /** Constructor
       */
      QualityTestReport();

      /** Copy constructor
       */
      QualityTestReport(const QualityTestReport &qreport);

      /** Assignment operator
       */
      QualityTestReport &operator=(const QualityTestReport &qreport);

      /**
       * [toJson description]
       * @param value [description]
       */
      void toJson(json &value) const;

      /**
       * [fromJson description]
       * @param value [description]
       */
      void fromJson(const json &value);

    public:
      std::string m_qualityTestName;
      std::string m_qualityTestType;
      std::string m_qualityTestDescription;
      std::string m_monitorElementName;
      std::string m_monitorElementType;
      std::string m_monitorElementPath;
      std::string m_message;
      QualityFlag m_qualityFlag;
      float m_quality;
      json m_extraInfos;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    /** QReportStorage class
     */
    class QReportStorage {
    public:
      /** Constructor
       */
      QReportStorage();

      /** Add report to list. If report already exists, replace it.
       *  Comparison made from :
       *    - monitor element name
       *    - monitor element type
       *    - quality test name
       */
      void addReport(const QReport &report, bool warnOnReplace = true);

      /** Add reports to list. If reports already exists, replace it.
       *  Comparison made from :
       *    - monitor element name
       *    - monitor element type
       *    - quality test name
       */
      void addReports(const QReportMap &reports, bool warnOnReplace = true);

      /** Get a specific report
       */
      StatusCode report(const std::string &path, const std::string &name, const std::string &qualityTestName,
                        QReport &report);

      /** Get all reports of the monitor element
       */
      StatusCode reports(const std::string &path, const std::string &name, QReportMap &reports);

      /** Get all reports of the monitor element with quality higher than a limit (range [0,1])
       */
      StatusCode reportsQualityHigher(const std::string &path, const std::string &name, float qlimit,
                                      QReportMap &reports);

      /** Get all reports of the monitor element with quality lower than a limit (range [0,1])
       */
      StatusCode reportsQualityLower(const std::string &path, const std::string &name, float qlimit,
                                     QReportMap &reports);

      /** Get all reports
       */
      const QReportContainer &reports();

      /** Get all reports with quality higher than a limit (range [0,1])
       */
      StatusCode reportsQualityHigher(float qlimit, QReportContainer &reports);

      /** Get all reports with quality lower than a limit (range [0,1])
       */
      StatusCode reportsQualityLower(float qlimit, QReportContainer &reports);

      /** Clear all contents
       */
      void clear();

    private:
      QReportContainer m_reports;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    /** QualityTest class
     */
    class QualityTest {
    public:
      /** Constructor
       */
      QualityTest(const std::string &type, const std::string &name);

      /** Destructor
       */
      virtual ~QualityTest();

      /** Get the quality test type
       */
      const std::string &type() const;

      /** Get the quality test name (unique identifier)
       */
      const std::string &name() const;

      /** Get the quality test description
       */
      const std::string &description() const;

      /** Perform the quality test result and fill the quality test report
       */
      void run(MonitorElementPtr monitorElement, QualityTestReport &report);

      /** Read the settings from the xml handle
       */
      virtual StatusCode readSettings(const dqm4hep::core::TiXmlHandle xmlHandle) = 0;

      /** Initialize the quality test.
       */
      virtual StatusCode init();
      
      /**
       *  @brief  Whether the monitor element has enough statistics to perform the qtest
       *
       *  @param  monitorElement the monitor element to check
       */
      virtual bool enoughStatistics(MonitorElementPtr monitorElement) const;

      /**
       *  @brief  Set the warning and error limits on quality test result.
       *          The limits must be ordered as 0 < error < warning < 1, else throws an exception
       *
       *  @param  warning the warning limit
       *  @param  error the error limit
       */
      void setLimits(float warning, float error);

      /**
       *  @brief  Get the warning limit
       */
      float warningLimit() const;

      /**
       *  @brief  Get the error limit
       */
      float errorLimit() const;

    protected:
      /** Runs a quality test on the given monitor element and return a quality estimate
       */
      virtual void userRun(MonitorElementPtr monitorElement, QualityTestReport &report) = 0;

      /** Fill basic info in the qtest report.
       *  Must be called at start of qtest run
       */
      void fillBasicInfo(MonitorElementPtr monitorElement, QualityTestReport &report) const;

    private:
      std::string m_type = {""};  ///< Quality test type (usually class name)
      std::string m_name = {""};  ///< Quality test name
      float m_warningLimit = {0}; ///< The quality test warning threshold
      float m_errorLimit = {0};   ///< The quality test error threshold

    protected:
      std::string m_description; ///< Quality test description

    public:
      static constexpr float defaultWarningLimit = {0.8};
      static constexpr float defaultErrorLimit = {0.5};
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    /** QualityTestFactory class
     */
    class QualityTestFactory {
    public:
      /** Destructor
       */
      virtual ~QualityTestFactory();

      /** Create a quality test
       */
      virtual QTestPtr createQualityTest(const std::string &name) const = 0;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    inline StatusCode QualityTest::init() {
      return STATUS_CODE_SUCCESS;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    inline bool QualityTest::enoughStatistics(MonitorElementPtr /*monitorElement*/) const {
      return true;
    }

    //-------------------------------------------------------------------------------------------------

    inline QualityTestFactory::~QualityTestFactory() {
      /* nop */
    }
  }
}

#endif //  DQM4HEP_QUALITYTEST_H
