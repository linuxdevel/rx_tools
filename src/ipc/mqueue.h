/*
 * mqueue a simplified linux mqueue interface
 * Copyright (C) 2019 by Arne Brune Olsen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _MQUEUE_H
#define _MQUEUE_H


int mqueue_open(void);
int mqueue_close(int qid);
int mqueue_send(int qid, const char *out);
int mqueue_rcv_nw(int qid, char **in);
void mqueue_flush(int qid);

#endif
