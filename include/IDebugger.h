/*
Copyright (C) 2006 - 2014 Evan Teran
                          eteran@alum.rit.edu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IDEBUGGER_20061101_H_
#define IDEBUGGER_20061101_H_

#include "IBreakpoint.h"
#include "IDebugEvent.h"
#include "IRegion.h"
#include "IProcess.h"
#include "ProcessInfo.h"
#include "Module.h"
#include "ThreadInfo.h"

#include <QByteArray>
#include <QHash>
#include <QMap>
#include <QString>
#include <QVector>
#include <QtPlugin>

class IState;
class QString;
class State;

class IDebugger {
public:
	typedef QHash<edb::address_t, IBreakpoint::pointer> BreakpointList;
	
public:
	virtual ~IDebugger() {}

public:
	// system properties
	virtual edb::address_t      page_size() const = 0;
	virtual int                 pointer_size() const = 0;
	virtual quint64             cpu_type() const = 0;
	virtual bool                has_extension(quint64 ext) const = 0;
	virtual QMap<long, QString> exceptions() const = 0;
	
public:
	// important register names
	virtual QString stack_pointer() const = 0;
	virtual QString frame_pointer() const = 0;
	virtual QString instruction_pointer() const = 0;
	virtual edb::pid_t parent_pid(edb::pid_t pid) const = 0;
	
public:
	// process properties
    virtual QList<Module>           loaded_modules() const = 0;
	
public:
	// basic process management
	virtual bool attach(edb::pid_t pid) = 0;
	virtual bool open(const QString &path, const QString &cwd, const QList<QByteArray> &args) = 0;
	virtual bool open(const QString &path, const QString &cwd, const QList<QByteArray> &args, const QString &tty) = 0;
	virtual IDebugEvent::const_pointer wait_debug_event(int msecs) = 0;
	virtual void detach() = 0;
	virtual void get_state(State *state) = 0;
	virtual void kill() = 0;
	virtual void pause() = 0;
	virtual void resume(edb::EVENT_STATUS status) = 0;
	virtual void set_state(const State &state) = 0;
	virtual void step(edb::EVENT_STATUS status) = 0;

public:
	// thread support stuff (optional)
	virtual QList<edb::tid_t> thread_ids() const            { return QList<edb::tid_t>(); }
	virtual edb::tid_t        active_thread() const         { return static_cast<edb::tid_t>(-1); }
	virtual void              set_active_thread(edb::tid_t) {}
	virtual ThreadInfo        get_thread_info(edb::tid_t)   { return ThreadInfo(); }

public:
	// basic breakpoint managment
	virtual BreakpointList       backup_breakpoints() const = 0;
	virtual IBreakpoint::pointer add_breakpoint(edb::address_t address) = 0;
	virtual IBreakpoint::pointer find_breakpoint(edb::address_t address) = 0;
	virtual void                 clear_breakpoints() = 0;
	virtual void                 remove_breakpoint(edb::address_t address) = 0;

public:
	virtual QString format_pointer(edb::address_t address) const = 0;

public:
	virtual IState *create_state() const = 0;
	
public:
	// NULL if not attached
	virtual IProcess *process() const = 0;

public:
	virtual QMap<edb::pid_t, ProcessInfo> enumerate_processes() const = 0;
};

Q_DECLARE_INTERFACE(IDebugger, "EDB.IDebugger/1.0")

#endif
