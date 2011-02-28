#include "dbstatistics.h"

#include "../libafanasy/job.h"

#include "dbattr.h"

using namespace afsql;

const QString DBStatistics::TableName("statistics");

DBStatistics::DBStatistics()
{
   dbAddAttr( new DBAttrQString( DBAttr::_annotation,        &annotation       ));
   dbAddAttr( new DBAttrQString( DBAttr::_blockname,         &blockname        ));
   dbAddAttr( new DBAttrQString( DBAttr::_jobname,           &jobname          ));
   dbAddAttr( new DBAttrQString( DBAttr::_description,       &description      ));
   dbAddAttr( new DBAttrQString( DBAttr::_hostname,          &hostname         ));
   dbAddAttr( new DBAttrQString( DBAttr::_service,           &service          ));
   dbAddAttr( new DBAttrUInt32( DBAttr::_tasksdone,         &tasksdone        ));
   dbAddAttr( new DBAttrUInt32( DBAttr::_tasksnum,          &tasksnum         ));
   dbAddAttr( new DBAttrUInt32( DBAttr::_taskssumruntime,   &taskssumruntime  ));
   dbAddAttr( new DBAttrUInt32( DBAttr::_time_done,         &time_done        ));
   dbAddAttr( new DBAttrUInt32( DBAttr::_time_started,      &time_started     ));
   dbAddAttr( new DBAttrQString( DBAttr::_username,          &username         ));
}

DBStatistics::~DBStatistics()
{
}

void DBStatistics::addJob( const af::Job * job, QStringList * queries)
{
   // Inserting each block in table:
   for( int b = 0; b < job->getBlocksNum(); b++)
   {
      // Get job parameters:
      jobname        = job->getName();
      description    = job->getDescription();
      annotation     = job->getAnnontation();
      username       = job->getUserName();
      hostname       = job->getHostName();
      time_started   = job->getTimeStarted();
      time_done      = job->getTimeDone();

      // Get block parameters:
      af::BlockData * block = job->getBlock(b);
      blockname = block->getName();
      service = block->getService();
      tasksnum = block->getTasksNum();
      tasksdone = block->getProgressTasksDone();
      taskssumruntime = job->getBlock(b)->getProgressTasksSumRunTime();

      // Insert row:
      dbInsert( queries);
   }
}
