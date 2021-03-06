/*
 * Copyright (C) 2019 by Martin Dejean
 *
 * This file is part of Xhu.
 * Xhu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Xhu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Xhu.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include "xhu_csound_wrapper.h"
#include "xhu_debug.h"
#include "xhu_table.h"

void xhu_create_sample_table(xhu_sample_table_t* const table)
{
    char message[128];
    sprintf(
            message,
            "f %u 0 0 %u \"%s\" %f %u %u",
            table->base.number,
            table->base.gen_routine,
            table->filename,
            table->skip_time,
            table->format,
            table->channel
            );
    xhu_send_message(message);
    
    while (!xhu_table_exists(table->base.number)); // TODO: replace with safer solution
}

void xhu_create_immediate_table(xhu_immediate_table_t* const table)
{
    if (table->value_count > table->base.size)
    {
        XHU_LOG_ERROR("Value count can not exceed table size for immediate table.")
        return;
    }
    
    xhu_u32_t values_string_size = 2 * table->value_count + 1;
    char values_string[values_string_size];
    
    for (xhu_u32_t i = 0; i < table->value_count; i += 2)
    {
        values_string[i] = ' ';
        values_string[i + 1] = table->values[i];
    }
    
    values_string[values_string_size] = '\0';
    
    char message[values_string_size + 64];
    
    sprintf(
            message,
            "f %u 0 0 %u %s",
            table->base.number,
            table->base.gen_routine,
            values_string
            );
    
    xhu_send_message(message);
    
    while (!xhu_table_exists(table->base.number)); // TODO: replace with safer solution
}

void xhu_create_segment_table(xhu_segment_table_t* const table)
{
    //    xhu_u32_t segments_string_size = 4 * table->segment_count + 1;
    //    char segments_string[segments_string_size];
    //    xhu_f32_t total_length = 0;
    //
    //    for (xhu_u32_t i = 0; i < table->segment_count; ++i)
    //    {
    //        segments_string[i] = " ";
    //        char value_string[1079];
    //        segments_string[i] = "";
    //        segments_string[i] = " ";
    //        segments_string[i] = "";
    //        total_length += table->segments[i].length;
    //    }
    //
    //    if (total_length < table->base.size)
    //    {
    //        XHU_LOG_WARN("Segment length sum is less than table size. Padding table end with zeros.");
    //    }
    //
    //    if (total_length > table->base.size)
    //    {
    //        XHU_LOG_WARN("Segment length sum is bigger than table size. Excess segments will not be included.");
    //    }
    //
    //    for (xhu_u32_t i = 0; i < numSegments; i++)
    //    {
    //        message += " " + xhu_to_string<xhu_f32_t>(table->segments.at(i).value);
    //        message += " " + xhu_to_string<xhu_f32_t>(table->segments.at(i).length);
    //    }
    //
    //
    ////    xhu_str_t message = "f " + xhu_to_string<xhu_s32_t>(table->number);
    ////    message += " 0 " + xhu_to_string<xhu_s32_t>(table->size) + " -7";
    ////
    ////    for (xhu_s32_t i = 0; i < numSegments; i++)
    ////    {
    ////        message += " " + xhu_to_string<xhu_f32_t>(table->segments.at(i).value);
    ////        message += " " + xhu_to_string<xhu_f32_t>(table->segments.at(i).length);
    ////    }
    //
    //    xhu_send_message(message);
    //
    //    while (!xhu_table_exists(table->number));
}

