#include "Manager/ShaderManager.h"
#include "Common/OpenGL.h"

ShaderManager::Shader::Shader()
{
	this->ID = 0;
	this->shaderType = Shader::UNKNOWN;
	return;
}

ShaderManager::Shader::~Shader()
{
	return;
}

std::string ShaderManager::Shader::GetShaderTypeString(void)
{
	switch (this->shaderType)
	{
	case Shader::VERTEX_SHADER:
		return "VERTEX_SHADER";
		break;
	case Shader::FRAGMENT_SHADER:
		return "FRAGMENT_SHADER";
		break;
	case Shader::UNKNOWN:
	default:
		return "UNKNOWN_SHADER_TYPE";
		break;
	}
	// Should never reach here...
	return "UNKNOWN_SHADER_TYPE";
}


//// TODO: For the students to do, because it's FUN, FUN, FUN
//std::map< std::string /*name of uniform variable*/,
//		    unsigned int /* uniform location ID */ > 
//						mapUniformName_to_UniformLocation;

// Look up the uniform inside the shader, then save it, if it finds it
bool ShaderManager::ShaderProgram::LoadUniformLocation(std::string variableName)
{
	// 
	GLint uniLocation = glGetUniformLocation(this->ID,
		variableName.c_str());
	// Did it find it (not -1)
	if (uniLocation == -1)
	{	// Nope.
		return false;
	}
	// Save it
	this->mapUniformNameToUniformLocation[variableName.c_str()] = uniLocation;

	return true;
}

ShaderManager::ShaderProgram::ShaderProgram()
{
}

ShaderManager::ShaderProgram::~ShaderProgram()
{
}

// Look up the uniform location and save it.
int ShaderManager::ShaderProgram::GetUniformIDFromName(std::string name)
{
	std::map< std::string /*name of uniform variable*/,
		int /* uniform location ID */ >::iterator
		itUniform = this->mapUniformNameToUniformLocation.find(name);

	if (itUniform == this->mapUniformNameToUniformLocation.end())
	{
		return -1;		// OpenGL uniform not found value
	}

	return itUniform->second;		// second if the "int" value
}
