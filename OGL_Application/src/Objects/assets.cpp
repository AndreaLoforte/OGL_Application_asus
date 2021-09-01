#include<assets.h>

#include<applicationObject.h>
#include<objectCollector.h>
#include<triangle_b.h>
#include<triangle_tb.h>
#include<point.h>
#include<Box_physical.h>
#include<object1.h>
#include<grid.h>
#include<surface.h>
#include<ground.h>
#include<polygon.h>
#include<sphere.h>
#include<frameofref.h>
#include<my_particle.h>
#include<gun.h>
#include<enemy.h>
#include<playerCharacter.h>
#include<boxAABB.h>
#include<activeObjectManager.h>


namespace AssetNS {




	std::vector< collectorNS::ApplicationObjectCollector*>  Assets::assetsList;
	std::map<std::string, int> Assets::assetIndex;
	int Assets::mapSize;
	std::vector<myobjectNS::ApplicationObject*> Assets::assetAOList;
	std::map<std::string, int > Assets::assetAOindex;
	



	void Assets::init() 
	{

		/*INSERTING APPLICATION OBJECT IN ASSET LIST CANNOT BE DONE IN ONE STEP: 
		1) INSERT APPLICATION OBJECT INTO ASSET AO LIST
		2) APPLICATION OBJECTS HAVE A METHODS getCollector() THAT RETURNS 
		A COLLECTOR FILLED WITH THE OBJECT THAT CALLED getCollector()*/


		//assetAOList.push_back(new myobjectNS::Particle("particle"));
		assetAOList.push_back(new myobjectNS::Grid("grid"));
		assetAOList.push_back(new myobjectNS::Surface("surface"));
		//assetAOList.push_back(new myobjectNS::GroundSurface("groundSurface"));
		assetAOList.push_back(new myobjectNS::Polygon("polygon"));
		assetAOList.push_back(new myobjectNS::Build("object1"));//dentro file object1
		assetAOList.push_back(new myobjectNS::Sphere("sphere"));
		//assetAOList.push_back(new myobjectNS::FrameOfRef("frameOfRef"));
		assetAOList.push_back(new myobjectNS::Box_physical("Box_physical"));
		//assetAOList.push_back(new myobjectNS::BoxAABB("boxAABB"));
		assetAOList.push_back(new myobjectNS::Triangle("triangle"));
		assetAOList.push_back(new myobjectNS::Point("point"));
		assetAOList.push_back(new myobjectNS::Triangle_tb("triangle_tb"));
	

		/*NOW CALLING getCollector() FOR EACH APPLICATION OBJECT*/
	
		for (int i = 0; i < assetAOList.size(); i++)
		{//da ogni ApplicationObject ottengo un collettore usando la funzione getCollector()
			//assetsList.push_back(assetAOList[i]->getCollector());
			assetsList.push_back(collectorNS::ApplicationObjectCollector::getCollector(assetAOList[i]));

			//assetAOindex contiene indicizza la posizione degli ApplicationObject nel vettore assetAOList
			assetAOindex.emplace(std::pair<std::string, int>{ assetAOList[i]->AOobjectName, i });
		}

		/*COLLECTOR ARE INSTERTED DIRECTLY INTO THE ASSET LIST*/
		assetsList.push_back(new myobjectNS::EnemyOC("Enemy"));
		assetsList.push_back(new myobjectNS::PlayerCharacterOC());
		assetsList.push_back(new myobjectNS::GroundSurfaceOC("groundSurface"));
		assetsList.push_back(new myobjectNS::FrameOfRefOC("frame_of_Ref"));

		//ogni applicationObject viene wrappato in un collector
		//un collector pu� contenere pi� object
		//ogni collector � un asset.
		/*mapSize = assetsList.size();*/
		for (int i = 0; i < assetsList.size(); i++)
			//assetIndex.insert(std::pair<std::string, int>{assetsList[i]->collectorID, i });
			assetIndex.insert(std::pair<std::string, int>{assetsList[i]->getCollectorName(), i });



	}

	myobjectNS::ApplicationObject* Assets::getNewObject(std::string objName) {

		//da qui recupero i collettori che entrano gi� come collettori
		for (int i = 0; i < assetsList.size(); i++)
			for (int j = 0; j < assetsList[i]->getSize(); j++)
				if (assetsList[i]->getSubObject(j)->AOobjectName == objName)
					return assetsList[i]->getSubObject(j);
	}

	myobjectNS::ApplicationObject* Assets::getNewObject(int index) {

		return assetAOList[index];

	}


	collectorNS::ApplicationObjectCollector* Assets::loadCollector(const string& Collname, const unsigned& number)
	{
		//checking if collector name is found among assets
		map<string, int>::iterator it = assetIndex.find(Collname);
		if (it == assetIndex.end()) return NULL;

		/*if found, load collector*/
		collectorNS::ApplicationObjectCollector* newColl = 
			assetsList[assetIndex.at(Collname)]->OCloadInstance(number);
		return newColl;
	}

	collectorNS::ActiveObjectCollector* Assets::loadActiveObject(const string& Collname, const unsigned& number)
	{
		//checking if collector name is found among assets
		map<string, int>::iterator it = assetIndex.find(Collname);
		if (it == assetIndex.end()) return NULL;

		/*if found, load collector*/
		collectorNS::ActiveObjectCollector* newColl =
			(assetsList[assetIndex.at(Collname)]->OCloadActiveObject(number));

		
		return newColl;
	}



	collectorNS::ApplicationObjectCollector* Assets::getNewCollector(std::string objName)
	{
		//da qui recupero i collettori che entrano gi� come collettori
		map<string, int>::iterator it = assetIndex.find(objName);
		if (it == assetIndex.end()) return NULL;
		collectorNS::ApplicationObjectCollector * newColl = assetsList[assetIndex.at(objName)]->OCgetNewInstance();
		return newColl;
	}


	collectorNS::ApplicationObjectCollector* Assets::getNewCollector(int index) {

		collectorNS::ApplicationObjectCollector* newColl = assetsList[index]->OCgetNewInstance();
		return newColl;

	}


}