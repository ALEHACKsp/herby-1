#include "sdk/object/entity.hpp"
#include "sdk/object/weapon.hpp"

#include "csgo/engine.hpp"

C_BaseEntity* C_BaseEntity::GetBaseEntity( const int index )
{
	const auto client_entity = csgo::m_client_entity_list->GetClientEntity( index );
	return (client_entity ? client_entity->GetBaseEntity() : nullptr);
}

C_BaseEntity* C_BaseEntity::GetBaseEntityFromHandle( const CBaseHandle base_handle )
{
	const auto client_entity = csgo::m_client_entity_list->GetClientEntityFromHandle( base_handle );
	return (client_entity ? client_entity->GetBaseEntity() : nullptr);
}

void C_BaseEntity::SetPredictionSeed(CUserCmd* cmd)
{
	static auto m_pPredictionRandomSeed = memory::scan< int* >("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04", 2, 1u);

	if (cmd)
		*m_pPredictionRandomSeed = cmd->random_seed;
	else
		*m_pPredictionRandomSeed = -1;
}

bool C_BaseAnimating::GetBoneTransform(matrix3x4_t* output, float time /*= 0.f*/)
{
	return SetupBones(output, 128, 256, time);
}

bool C_BaseAnimating::GetBonePosition( matrix3x4_t* bone_transform, const int bone, Vector& output )
{
	if( bone_transform )
	{
		for( auto i = 0; i < 3; i++ )
			output[ i ] = bone_transform[ bone ][ i ][ 3 ];
	}

	return ( !output.IsZero() && output.IsValid() );
}

bool C_BaseAnimating::GetBoneWorld(int index, matrix3x4_t* transform, Vector& output)
{
	if (transform)
	{
		for (auto i = 0; i < 3; i++)
			output[i] = transform[index][i][3];
	}

	return !output.IsZero();
}

bool C_BaseAnimating::GetBoxBoundWorld(int index, matrix3x4_t* transform, Vector& min, Vector& max)
{
	if (transform)
	{
		auto model = GetModel();

		if (model)
		{
			auto studio = csgo::m_model_info_client->GetStudioModel(model);

			if (studio)
			{
				auto box = studio->pHitbox(index, m_nHitboxSet());

				if (box)
				{
					min = box->bbmin.Transform(transform[box->bone]);
					max = box->bbmax.Transform(transform[box->bone]);
				}
			}
		}
	}

	return (!min.IsZero() && !max.IsZero());
}

bool C_BaseAnimating::GetBoxWorld(int index, matrix3x4_t* transform, Vector& output)
{
	Vector min = { };
	Vector max = { };

	if (GetBoxBoundWorld(index, transform, min, max))
		output = (min + max) * 0.5f;

	return !output.IsZero();
}

bool C_BaseAnimating::GetHitboxVector(int hitbox, Vector& out)
{
	matrix3x4_t mat[128];

	if (!GetBoneTransform(mat))
		return false;

	auto studio = csgo::m_model_info_client->GetStudioModel(GetModel());

	if (!studio)
		return false;

	auto set = studio->pHitboxSet(m_nHitboxSet());

	if (!set)
		return false;

	auto box = set->pHitbox(hitbox);

	if (!box)
		return false;

	Vector mins = { }, maxs = { };

	mins = box->bbmin.Transform(mat[box->bone]);
	maxs = box->bbmax.Transform(mat[box->bone]);

	if (mins.IsZero() || maxs.IsZero())
		return false;

	out = (mins + maxs) * 0.5f;

	return !(out.IsZero());
}

Vector C_BaseAnimating::GetHitboxPosition(int index)
{
	matrix3x4_t transform[128] = { };
	if (!GetBoneTransform(transform))
		return Vector::Zero;

	Vector position = { };
	if (!GetBoxWorld(index, transform, position))
		return Vector::Zero;

	return position;
}

C_BaseViewModel* C_BaseAttributeItem::GetBaseModel()
{
	auto base_model = reinterpret_cast<C_BaseViewModel*>(this);
	return base_model;
}
