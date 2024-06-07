/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*  Copyright (c) 2002-2024 Zuse Institute Berlin (ZIB)                      */
/*                                                                           */
/*  Licensed under the Apache License, Version 2.0 (the "License");          */
/*  you may not use this file except in compliance with the License.         */
/*  You may obtain a copy of the License at                                  */
/*                                                                           */
/*      http://www.apache.org/licenses/LICENSE-2.0                           */
/*                                                                           */
/*  Unless required by applicable law or agreed to in writing, software      */
/*  distributed under the License is distributed on an "AS IS" BASIS,        */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*  See the License for the specific language governing permissions and      */
/*  limitations under the License.                                           */
/*                                                                           */
/*  You should have received a copy of the Apache-2.0 license                */
/*  along with SCIP; see the file LICENSE. If not visit scipopt.org.         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   struct_message.h
 * @ingroup INTERNALAPI
 * @brief  datastructures for problem statistics
 * @author Tobias Achterberg
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_STRUCT_MESSAGE_H__
#define __SCIP_STRUCT_MESSAGE_H__


#include "scip/def.h"
#include "scip/type_message.h"

#ifdef __cplusplus
extern "C" {
#endif

/** message handler to redirect output */
struct SCIP_Messagehdlr
{
   SCIP_DECL_MESSAGEWARNING((*messagewarning));/**< warning message print method of message handler */
   SCIP_DECL_MESSAGEDIALOG((*messagedialog));/**< dialog message print method of message handler */
   SCIP_DECL_MESSAGEINFO((*messageinfo));    /**< info message print method of message handler */
   SCIP_DECL_MESSAGEHDLRFREE((*messagehdlrfree)); /**< destructor of message handler to free message handler data */
   SCIP_MESSAGEHDLRDATA* messagehdlrdata;    /**< message handler data */
   FILE*                 logfile;            /**< log file where to copy messages into */
   SCIP_Bool             quiet;              /**< should screen messages be suppressed? */
   char*                 warningbuffer;      /**< buffer for constructing complete warning output lines */
   char*                 dialogbuffer;       /**< buffer for constructing complete dialog output lines */
   char*                 infobuffer;         /**< buffer for constructing complete info output lines */
   int                   warningbufferlen;   /**< currently used space in the warning buffer */
   int                   dialogbufferlen;    /**< currently used space in the dialog buffer */
   int                   infobufferlen;      /**< currently used space in the info buffer */
   int                   nuses;              /**< number of message handler uses */
};

#ifdef __cplusplus
}
#endif

#endif
