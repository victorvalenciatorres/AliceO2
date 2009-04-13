//-*- Mode: C++ -*-
// ************************************************************************
// This file is property of and copyright by the ALICE HLT Project        *
// ALICE Experiment at CERN, All rights reserved.                         *
// See cxx source for full Copyright notice                               *
//                                                                        *
//*************************************************************************

#ifndef ALIHLTTPCCANEIGHBOURSFINDER_H
#define ALIHLTTPCCANEIGHBOURSFINDER_H


#include "AliHLTTPCCADef.h"
#include "AliHLTTPCCAGrid.h"
class AliHLTTPCCATracker;

/**
 * @class AliHLTTPCCANeighboursFinder
 *
 */
class AliHLTTPCCANeighboursFinder
{
  public:
    class AliHLTTPCCASharedMemory
    {
        friend class AliHLTTPCCANeighboursFinder;
      public:
#if !defined(HLTCA_GPUCODE)
        AliHLTTPCCASharedMemory()
            : fGridUp(), fGridDn(), fNHits( 0 ), fUpNHits( 0 ), fDnNHits( 0 ), fUpDx( 0 ), fDnDx( 0 ), fUpTx( 0 ), fDnTx( 0 ), fIRow( 0 ), fIRowUp( 0 ), fIRowDn( 0 ), fFirst( 0 ), fFirstDn( 0 ), fFirstUp( 0 ), fNRows( 0 ), fHitLinkUp( 0 ), fHitLinkDn( 0 ) {}

        AliHLTTPCCASharedMemory( const AliHLTTPCCASharedMemory& /*dummy*/ )
            : fGridUp(), fGridDn(), fNHits( 0 ), fUpNHits( 0 ), fDnNHits( 0 ), fUpDx( 0 ), fDnDx( 0 ), fUpTx( 0 ), fDnTx( 0 ), fIRow( 0 ), fIRowUp( 0 ), fIRowDn( 0 ), fFirst( 0 ), fFirstDn( 0 ), fFirstUp( 0 ), fNRows( 0 ), fHitLinkUp( 0 ), fHitLinkDn( 0 ) {}
        AliHLTTPCCASharedMemory& operator=( const AliHLTTPCCASharedMemory& /*dummy*/ ) { return *this; }
#endif
      protected:
        AliHLTTPCCAGrid fGridUp; // grid for the next row
        AliHLTTPCCAGrid fGridDn; // grid for the previous row
        int fNHits; // n hits
        int fUpNHits; // n hits in the next row
        int fDnNHits; // n hits in the prev row
        float fUpDx; // x distance to the next row
        float fDnDx; // x distance to the previous row
        float fUpTx; // normalized x distance to the next row
        float fDnTx; // normalized x distance to the previous row
        int fIRow; // row number
        int fIRowUp; // next row number
        int fIRowDn;// previous row number
        int fFirst; // index of the first hit
        int fFirstDn; // index of the first hit in the next row
        int fFirstUp;// index of the first hit in the previous row
        int fNRows; // number of rows
        short *fHitLinkUp; // links to the next row
        short *fHitLinkDn; // links to the previous  row
        float2 fA[256][20]; // temp memory
        unsigned short fB[256][20]; // temp memory
        unsigned short fGridContentUp[7000]; // grid content for the next row
        unsigned short fGridContentDn[7000];// grid content for the previous row
    };

    GPUd() static int NThreadSyncPoints() { return 2; }

    GPUd() static void Thread( int nBlocks, int nThreads, int iBlock, int iThread, int iSync,
                               AliHLTTPCCASharedMemory &smem, AliHLTTPCCATracker &tracker );

};


#endif
