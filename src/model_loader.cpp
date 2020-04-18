#include "model_loader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

HRESULT ModelLoader::LoadModel(std::string path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	

	std::string warn;
	std::string err;

	std::wstring::size_type position = path.find_last_of("\\/");
	model_dir = path.substr(0, position);
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), model_dir.c_str());

	if (!warn.empty())
	{
		std::wstring wwarn(warn.begin(), warn.end());
		wwarn = L"Tiny OBJ reader warning: " + wwarn + L"\n";
		OutputDebugString(wwarn.c_str());
	}

	if (!err.empty())
	{
		std::wstring werr(err.begin(), err.end());
		werr = L"Tiny OBJ reader error: " + werr + L"\n";
		OutputDebugString(werr.c_str());
	}

	if (!ret)
	{
		return -1;
	}

	typedef std::map<std::tuple<int, int, int>, UINT> indeces_map_type;
	//indeces_map_type indeces_map;

	std::vector<std::vector<FullVertex>> per_material_verteces(materials.size());
	std::vector<std::vector<UINT>> per_material_indeces(materials.size());
	std::vector<indeces_map_type> per_material_indeces_map(materials.size());
	 
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			// per-face material
			int material_id = shapes[s].mesh.material_ids[f];
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				std::tuple<int, int, int> idx_tuple = std::make_tuple(idx.vertex_index, idx.normal_index, idx.texcoord_index);
				if (per_material_indeces_map[material_id].count(idx_tuple) > 0)
				{
					per_material_indeces[material_id].push_back(per_material_indeces_map[material_id][idx_tuple]);
				}
				else 
				{
					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = -attrib.vertices[3 * idx.vertex_index + 2];
					tinyobj::real_t nx = (idx.normal_index > -1) ? attrib.normals[3 * idx.normal_index + 0] : 0.0f;
					tinyobj::real_t ny = (idx.normal_index > -1) ? attrib.normals[3 * idx.normal_index + 1] : 0.0f;
					tinyobj::real_t nz = (idx.normal_index > -1) ? -attrib.normals[3 * idx.normal_index + 2] : 0.0f;
					tinyobj::real_t tu = (idx.texcoord_index > -1) ? attrib.texcoords[2 * idx.texcoord_index + 0] : 0.0f;
					tinyobj::real_t tv = (idx.texcoord_index > -1) ? 1.0f - attrib.texcoords[2 * idx.texcoord_index + 1] : 0.0f;

					materials[material_id].diffuse;
					FullVertex vertex = {};
					vertex.position = { vx, vy, vz };
					vertex.diffuse_color = {
							materials[material_id].diffuse[0],
							materials[material_id].diffuse[1],
							materials[material_id].diffuse[2],

					};
					vertex.normal = { nx, ny, nz };
					vertex.texcoord = { tu, tv };

					per_material_indeces[material_id].push_back(per_material_verteces[material_id].size());
					per_material_indeces_map[material_id][idx_tuple] = per_material_verteces[material_id].size();
					per_material_verteces[material_id].push_back(vertex);
				}
			}
			index_offset += fv;
		}
	};

	for (size_t material_id = 0; material_id < GetMaterialNum(); material_id++) 
	{
		DrawCallParams params = {};
		params.start_index = indeces.size();
		params.start_vertex = verteces.size();

		verteces.insert(verteces.end(), per_material_verteces[material_id].begin(), per_material_verteces[material_id].end());
		indeces.insert(indeces.end(), per_material_indeces[material_id].begin(), per_material_indeces[material_id].end());

		params.index_num = static_cast<UINT>(per_material_indeces[material_id].size());
		per_material_draw_call_params.push_back(params);
	}

	return S_OK;
}

const FullVertex* ModelLoader::GetVertexBuffer() const
{
	return verteces.data();
}

const UINT ModelLoader::GetVertexBufferSize() const
{
	return static_cast<UINT>(verteces.size() * sizeof(FullVertex));
}

const UINT ModelLoader::GetVertexNum() const
{
	return static_cast<UINT>(verteces.size());
}

const UINT * ModelLoader::GetIndexBuffer() const
{
	return indeces.data();
}

const UINT ModelLoader::GetIndexBufferSize() const
{
	return static_cast<UINT>(indeces.size() * sizeof(UINT));
}

const UINT ModelLoader::GetIndexNum() const
{
	return static_cast<UINT>(indeces.size());
}

const UINT ModelLoader::GetMaterialNum() const
{
	return materials.size();
}

const DrawCallParams ModelLoader::GetDrawCallParams(UINT material_id) const
{
	return per_material_draw_call_params[material_id];
}

const std::string ModelLoader::GetTexturePath(UINT material_id) const
{
	return model_dir + "\\" + materials[material_id].diffuse_texname;
}

const bool ModelLoader::HasTexture(UINT material_id) const
{
	return !materials[material_id].diffuse_texname.empty();
}

const UINT ModelLoader::GetTextureNum() const
{
	UINT texture_num = 0;
	for (UINT material_id = 0; material_id < GetMaterialNum(); material_id++)
	{
		if (HasTexture(material_id))
		{
			texture_num++;
		}
	}

	return texture_num;
}
