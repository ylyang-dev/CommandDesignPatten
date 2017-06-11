#include <iostream>
#include <vector>

using namespace std;

#define	MAX_COMMAND_NUM		10


enum Receiver
{
	LIGHT = 0,
	FAN,
	OVEN,
	NONE
};


// Receiver class
class Light
{
	public:
		void on ()
		{
			cout << "The light is on\n";
		}

		void off ()
		{
			cout << "The light is off\n";
		}
};

class Fan
{
public:
	void on ()
	{
		cout << "The fan is on\n";
	}

	void off ()
	{
		cout << "The fan is off\n";
	}
};

class Oven
{
public:
	void on ()
	{
		cout << "The oven is on\n";
	}

	void off ()
	{
		cout << "The oven is off\n";
	}
};


// Command Interface
class Command
{
	public:
		virtual void execute () = 0;
};

// Command for null
class NullCommand : public Command
{
	public:
		void execute ()
		{
			cout << "Null command: do nothing\n";
		}
};

// Command for turning on the light (receiver + action)
class LightOnCommand : public Command
{
	private:
		Light	*m_light;

	public:
		LightOnCommand ( Light *light ) :
			m_light ( light )
		{
		}

		void execute ()
		{
			m_light->on ();
		}
};

// Command for turning off the light
class LightOffCommand : public Command
{
	private:
		Light	*m_light;

	public:
		LightOffCommand ( Light *light ) :
			m_light ( light )
		{
		}

		void execute ()
		{
			m_light->off ();
		}
};

// Command for turning on the fan (receiver + action)
class FanOnCommand : public Command
{
	private:
		Fan	*m_fan;

	public:
		FanOnCommand ( Fan *fan ) :
			m_fan ( fan )
		{
		}

		void execute ()
		{
			m_fan->on ();
		}
};

// Command for turning off the fan
class FanOffCommand : public Command
{
	private:
		Fan	*m_fan;

	public:
		FanOffCommand ( Fan *fan ) :
			m_fan ( fan )
		{
		}

		void execute ()
		{
			m_fan->off ();
		}
};

// Command for turning on the oven (receiver + action)
class OvenOnCommand : public Command
{
	private:
		Oven	*m_oven;

	public:
		OvenOnCommand ( Oven *oven ) :
			m_oven ( oven )
		{
		}

		void execute ()
		{
			m_oven->on ();
		}
};

// Command for turning off the oven
class OvenOffCommand : public Command
{
	private:
		Oven	*m_oven;

	public:
		OvenOffCommand ( Oven *oven ) :
			m_oven ( oven )
		{
		}

		void execute ()
		{
			m_oven->off ();
		}
};


// Simple Command Invoker (stores the ConcreteCommand object)
class SimpleCommandRemoteControl
{
	private:
		Command *m_cmd;

	public:
		void setCommand ( Command *cmd )
		{
			m_cmd = cmd;
		}

		void buttonPressed ()
		{
			m_cmd->execute ();
		}
};


// Simple command test
void SimpleCommandTest ()
{
	// Receiver
	Light *light = new Light;

	// concrete command objects
	LightOnCommand  *lightOn  = new LightOnCommand  ( light );
	LightOffCommand *lightOff = new LightOffCommand ( light );

	// invoker objects
	SimpleCommandRemoteControl *control = new SimpleCommandRemoteControl;

	// execute
	control->setCommand ( lightOn );
	control->buttonPressed ();

	control->setCommand ( lightOff );
	control->buttonPressed ();

	delete light, lightOn, lightOff, control;
}


// Macro Command Invoker (stores the ConcreteCommand object)
class MacroCommandRemoteControl
{
	private:
		vector < Command * > m_on_cmd, m_off_cmd;

	public:
		MacroCommandRemoteControl () :
			m_on_cmd ( MAX_COMMAND_NUM ), m_off_cmd ( MAX_COMMAND_NUM )
		{
			Command *nullCmd = new NullCommand;
			for ( int i = 0; i < MAX_COMMAND_NUM; i++ )
			{
				m_on_cmd  [ i ] = nullCmd;
				m_off_cmd [ i ] = nullCmd;
			}
		}

		void setCommand ( Receiver id, Command *onCmd, Command *offCmd )
		{
			m_on_cmd  [ id ] = onCmd;
			m_off_cmd [ id ] = offCmd;
		}

		void onButtonPressed ( Receiver id )
		{
			m_on_cmd [ id ]->execute ();
		} 

		void offButtonPressed ( Receiver id )
		{
			m_off_cmd [ id ]->execute ();
		}
};


// Macro command test
void MacroCommandTest ()
{
	// Receiver
	Light *light = new Light;
	Fan *fan = new Fan;
	Oven *oven = new Oven;

	// concrete command objects
	LightOnCommand  *lightOn  = new LightOnCommand  ( light );
	LightOffCommand *lightOff = new LightOffCommand ( light );
	FanOnCommand  *fanOn  = new FanOnCommand  ( fan );
	FanOffCommand *fanOff = new FanOffCommand ( fan );
	OvenOnCommand  *ovenOn  = new OvenOnCommand  ( oven );
	OvenOffCommand *ovenOff = new OvenOffCommand ( oven );

	NullCommand *nullOn  = new NullCommand ();
	NullCommand *nullOff = new NullCommand ();

	// invoker objects
	MacroCommandRemoteControl *control = new MacroCommandRemoteControl;

	// execute
	control->setCommand ( LIGHT, lightOn, lightOff );
	control->onButtonPressed  ( LIGHT );
	control->offButtonPressed ( LIGHT );

	control->setCommand ( FAN, fanOn, fanOff );
	control->onButtonPressed  ( FAN );
	control->offButtonPressed ( FAN );

	control->setCommand ( OVEN, ovenOn, ovenOff );
	control->onButtonPressed  ( OVEN );
	control->offButtonPressed ( OVEN );

	control->setCommand ( NONE, nullOn, nullOff );
	control->onButtonPressed  ( NONE );

	delete light, lightOn, lightOff;
	delete fan, fanOn, fanOff;
	delete oven, ovenOn, ovenOff;
	delete control;
}


int main ()
{
	cout << "Simple command test: \n";
	SimpleCommandTest ();
	cout << "\n\n";

	cout << "Macro command test: \n";
	MacroCommandTest ();
	cout << "\n\n";
}
