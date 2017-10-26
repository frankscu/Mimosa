//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// The code was written by :
//	^Claudio Andenna  claudio.andenna@ispesl.it, claudio.andenna@iss.infn.it
//      *Barbara Caccia barbara.caccia@iss.it
//      with the support of Pablo Cirrone (LNS, INFN Catania Italy)
//	with the contribute of Alessandro Occhigrossi*
//
// ^INAIL DIPIA - ex ISPESL and INFN Roma, gruppo collegato Sanità, Italy
// *Istituto Superiore di Sanità and INFN Roma, gruppo collegato Sanità, Italy
//  Viale Regina Elena 299, 00161 Roma (Italy)
//  tel (39) 06 49902246
//  fax (39) 06 49387075
//
// more information:
// http://g4advancedexamples.lngs.infn.it/Examples/medical-linac
//
//*******************************************************//


#include "MimosaPrimaryGeneratorActionMessenger.hh"
#include "MimosaPrimaryGeneratorAction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

MimosaPrimaryGeneratorActionMessenger::MimosaPrimaryGeneratorActionMessenger(MimosaPrimaryGeneratorAction *PMimosaPrimaryGeneratorAction) : pMimosaPrimaryGeneratorAction(PMimosaPrimaryGeneratorAction)
{

	particleType=new G4UIcmdWithAString("/beam/particle",this);
	particleType->SetDefaultValue("mu-");
	particleType->SetGuidance("type of particle generator source  (randomTarget, phaseSpace)");

	gunEnergy=new G4UIcmdWithADoubleAndUnit("/beam/energy", this);
	gunEnergy->SetDefaultUnit("GeV");
	gunEnergy->SetDefaultValue(20.);
	gunEnergy->SetGuidance("mean energy of the primary particles");

	gunPosXYSpread=new G4UIcmdWithADoubleAndUnit("/beam/posXYSpread", this);
	gunPosXYSpread->SetDefaultUnit("mm");
	gunPosXYSpread->SetDefaultValue(1.);
	gunPosXYSpread->SetGuidance("X-Y position of the gun");

	gunPosZ=new G4UIcmdWithADoubleAndUnit("/beam/posZ", this);
	gunPosZ->SetDefaultUnit("mm");
	gunPosZ->SetDefaultValue(1.);
	gunPosZ->SetGuidance("Z position of the gun");

}

MimosaPrimaryGeneratorActionMessenger::~MimosaPrimaryGeneratorActionMessenger(void)
{
  delete gunPosXYSpread;
  delete gunPosZ;
  delete gunEnergy;
  delete particleType;
}
void MimosaPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{

	if (cmd==particleType){
    pMimosaPrimaryGeneratorAction->SetParticleType(newValue);
  }

	if (cmd==gunEnergy)
	{
		gunEnergy->GetNewUnitValue(newValue);
		pMimosaPrimaryGeneratorAction->SetGunEnergy(gunEnergy->GetNewDoubleValue(newValue));
	}

	if (cmd==gunPosXYSpread)
	{
		gunPosXYSpread->GetNewUnitValue(newValue);
		pMimosaPrimaryGeneratorAction->SetGunPosXYSpread(gunPosXYSpread->GetNewDoubleValue(newValue));
	}

	if (cmd==gunPosZ)
	{
		gunPosZ->GetNewUnitValue(newValue);
		pMimosaPrimaryGeneratorAction->SetGunPosZ(gunPosZ->GetNewDoubleValue(newValue));
	}


}
