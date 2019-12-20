#pragma once
#ifndef _Model_PlnEntity_Header
#define _Model_PlnEntity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Entity2d_ChainFwd.hxx>

#include <gp_Ax22d.hxx>

#include <memory>

namespace AutLib
{

	class Model_PlnEntitySystem
	{

		/*private Data*/

		gp_Ax22d theSystem_;

	protected:

		virtual void SetSystem(const gp_Ax22d& theSystem)
		{
			theSystem_ = theSystem;
		}

	public:

		Model_PlnEntitySystem()
		{}

		const gp_Ax22d& System() const
		{
			return theSystem_;
		}

		gp_Ax22d& ChangeSystem()
		{
			return theSystem_;
		}
	};

	class Model_PlnEntityID
		: public Global_Indexed
		, public Global_Named
	{};

	class Model_PlnEntityDiscrete
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Chain> theMesh_;

	protected:

		std::shared_ptr<Entity2d_Chain>& ChangeMesh()
		{
			return theMesh_;
		}

		void SetMesh(const std::shared_ptr<Entity2d_Chain>& theMesh)
		{
			theMesh_ = theMesh;
		}

	public:

		Model_PlnEntityDiscrete()
		{}

		const std::shared_ptr<Entity2d_Chain>& Mesh() const
		{
			return theMesh_;
		}

		void ReleaseMesh()
		{
			theMesh_.reset();
		}

		virtual void Discrete() = 0;
	};


}

#endif // !_Model_PlnEntity_Header
