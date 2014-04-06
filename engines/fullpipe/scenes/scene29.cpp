/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "fullpipe/fullpipe.h"

#include "fullpipe/objectnames.h"
#include "fullpipe/constants.h"

#include "fullpipe/gameloader.h"
#include "fullpipe/motion.h"
#include "fullpipe/scenes.h"
#include "fullpipe/statics.h"

#include "fullpipe/interaction.h"
#include "fullpipe/behavior.h"


namespace Fullpipe {

struct WalkingBearder {
	StaticANIObject *ani;
	int wbflag;
	int wbcounter;
};

void scene29_initScene(Scene *sc) {
	g_vars->scene29_porter = sc->getStaticANIObject1ById(ANI_PORTER, -1);
	g_vars->scene29_shooter1 = sc->getStaticANIObject1ById(ANI_SHOOTER1, -1);
	g_vars->scene29_shooter2 = sc->getStaticANIObject1ById(ANI_SHOOTER2, -1);
	g_vars->scene29_ass = sc->getStaticANIObject1ById(ANI_ASS, -1);

	g_vars->scene29_balls.numBalls = 0;
	g_vars->scene29_balls.pTail = 0;
	g_vars->scene29_balls.field_8 = 0;
	g_vars->scene29_balls.pHead = 0;

	free(g_vars->scene29_balls.cPlex);
	g_vars->scene29_balls.cPlex = 0;

	StaticANIObject *ani;

	g_vars->scene29_greenBalls.numBalls = 0;
	g_vars->scene29_greenBalls.pTail = 0;
	g_vars->scene29_greenBalls.field_8 = 0;
	g_vars->scene29_greenBalls.pHead = 0;

	free(g_vars->scene29_greenBalls.cPlex);
	g_vars->scene29_greenBalls.cPlex = 0;

	ani = sc->getStaticANIObject1ById(ANI_SHELL_GREEN, -1);
	Ball *b = g_vars->scene29_balls.sub04(g_vars->scene29_balls.field_8, 0);
	b->ani = ani;

	if (g_vars->scene29_balls.field_8)
		g_vars->scene29_balls.field_8->p0 = b;
	else
		g_vars->scene29_balls.pHead = b;

	g_vars->scene29_balls.field_8 = b;

	for (int i = 0; i < 2; i++) {
		StaticANIObject *newani = new StaticANIObject(ani);

		sc->addStaticANIObject(newani, 1);

		b = g_vars->scene29_balls.sub04(g_vars->scene29_balls.field_8, 0);
		b->ani = ani;

		if (g_vars->scene29_balls.field_8)
			g_vars->scene29_balls.field_8->p0 = b;
		else
			g_vars->scene29_balls.pHead = b;

		g_vars->scene29_balls.field_8 = b;
	}

	g_vars->scene29_redBalls.numBalls = 0;
	g_vars->scene29_redBalls.pTail = 0;
	g_vars->scene29_redBalls.field_8 = 0;
	g_vars->scene29_redBalls.pHead = 0;

	free(g_vars->scene29_redBalls.cPlex);
	g_vars->scene29_redBalls.cPlex = 0;

	g_vars->scene29_var07.numBalls = 0;
	g_vars->scene29_var07.pTail = 0;
	g_vars->scene29_var07.field_8 = 0;
	g_vars->scene29_var07.pHead = 0;

	free(g_vars->scene29_var07.cPlex);
	g_vars->scene29_var07.cPlex = 0;

	ani = sc->getStaticANIObject1ById(ANI_SHELL_RED, -1);

	b = g_vars->scene29_redBalls.sub04(g_vars->scene29_redBalls.field_8, 0);
	b->ani = ani;

	if (g_vars->scene29_redBalls.field_8)
		g_vars->scene29_redBalls.field_8->p0 = b;
	else
		g_vars->scene29_redBalls.pHead = b;

	g_vars->scene29_redBalls.field_8 = b;

	for (int i = 0; i < 2; i++) {
		StaticANIObject *newani = new StaticANIObject(ani);

		sc->addStaticANIObject(newani, 1);

		b = g_vars->scene29_redBalls.sub04(g_vars->scene29_redBalls.field_8, 0);
		b->ani = ani;

		if (g_vars->scene29_redBalls.field_8)
			g_vars->scene29_redBalls.field_8->p0 = b;
		else
			g_vars->scene29_redBalls.pHead = b;

		g_vars->scene29_redBalls.field_8 = b;
	}

	g_vars->scene29_var19.clear();

	ani = new StaticANIObject(g_fp->accessScene(SC_COMMON)->getStaticANIObject1ById(ANI_BEARDED_CMN, -1));

	ani->_statics = ani->getStaticsById(ST_BRDCMN_EMPTY);

	sc->addStaticANIObject(ani, 1);

	WalkingBearder *wb = new WalkingBearder;

	wb->ani = ani;
	wb->wbflag = 0;
	wb->wbcounter = 0;

	g_vars->scene29_var19.push_back(wb);

	g_vars->scene29_var09 = 0;
	g_vars->scene29_var10 = 0;
	g_vars->scene29_var11 = 0;
	g_vars->scene29_var12 = 0;
	g_vars->scene29_var13 = 0;
	g_vars->scene29_var14 = 75;
	g_vars->scene29_var15 = 0;
	g_vars->scene29_var16 = 0;
	g_vars->scene29_var17 = 0;
	g_vars->scene29_var18 = 0;

	g_fp->setArcadeOverlay(PIC_CSR_ARCADE8);
}

void sceneHandler29_winArcade() {
	if (g_vars->scene29_shooter2->_flags & 4) {
		g_vars->scene29_var13 = 0;

		g_vars->scene29_shooter1->changeStatics2(ST_STR1_STAND);
		g_vars->scene29_shooter2->changeStatics2(ST_STR2_STAND);

		g_vars->scene29_shooter2->_flags &= 0xFFFB;

		StaticANIObject *ani;
		Ball *newball, *ball, *oldp0;

		while (g_vars->scene29_greenBalls.numBalls) {
			ball = g_vars->scene29_greenBalls.pHead;
			ani = g_vars->scene29_greenBalls.pHead->ani;
			oldp0 = g_vars->scene29_greenBalls.pHead->p0;
			g_vars->scene29_greenBalls.pHead = g_vars->scene29_greenBalls.pHead->p0;

			if (g_vars->scene29_greenBalls.pHead)
				oldp0->p1 = 0;
			else
				g_vars->scene29_greenBalls.field_8 = 0;

			ball->p0 = g_vars->scene29_greenBalls.pTail;
			g_vars->scene29_greenBalls.pTail = ball;
			g_vars->scene29_greenBalls.numBalls--;

			if (!g_vars->scene29_greenBalls.numBalls)
				g_vars->scene29_greenBalls.reset();

			ani->hide();

			newball = g_vars->scene29_balls.sub04(g_vars->scene29_balls.field_8, 0);
			newball->ani = ani;

			if (g_vars->scene29_balls.field_8)
				g_vars->scene29_balls.field_8->p0 = newball;
			else
				g_vars->scene29_balls.pHead = newball;

			g_vars->scene29_balls.field_8 = newball;
		}

		while (g_vars->scene29_var07.numBalls) {
			ball = g_vars->scene29_var07.pHead;
			ani = g_vars->scene29_var07.pHead->ani;
			oldp0 = g_vars->scene29_var07.pHead->p0;
			g_vars->scene29_var07.pHead = g_vars->scene29_var07.pHead->p0;

			if (g_vars->scene29_var07.pHead)
				oldp0->p1 = 0;
			else
				g_vars->scene29_var07.field_8 = 0;

			ball->p0 = g_vars->scene29_var07.pTail;
			g_vars->scene29_var07.pTail = ball;
			g_vars->scene29_var07.numBalls--;

			if (!g_vars->scene29_var07.numBalls) {
				g_vars->scene29_var07.numBalls = 0;
				g_vars->scene29_var07.pTail = 0;
				g_vars->scene29_var07.field_8 = 0;
				g_vars->scene29_var07.pHead = 0;

				free(g_vars->scene29_var07.cPlex);

				g_vars->scene29_var07.cPlex = 0;
			}

			ani->hide();

			newball = g_vars->scene29_redBalls.sub04(g_vars->scene29_redBalls.field_8, 0);
			newball->ani = ani;

			if (g_vars->scene29_redBalls.field_8)
				g_vars->scene29_redBalls.field_8->p0 = newball;
			else
				g_vars->scene29_redBalls.pHead = newball;

			g_vars->scene29_redBalls.field_8 = newball;
		}

		g_vars->scene29_ass->queueMessageQueue(0);
		g_vars->scene29_ass->_flags &= 0xFFFB;

		chainQueue(QU_SC29_ESCAPE, 1);
	}

	g_fp->setObjectState(sO_LeftPipe_29, g_fp->getObjectEnumState(sO_LeftPipe_29, sO_IsOpened));
}

void sceneHandler29_shootGreen() {
	if (g_vars->scene29_balls.numBalls) {
		int x = g_vars->scene29_shooter1->_ox - 113;
		int y = g_vars->scene29_shooter1->_oy - 48;
		StaticANIObject *ani = g_vars->scene29_balls.pHead->ani;
		Ball *oldhead = g_vars->scene29_balls.pHead;
		Ball *oldp0 = g_vars->scene29_balls.pHead->p0;

		g_vars->scene29_balls.pHead = g_vars->scene29_balls.pHead->p0;

		if (g_vars->scene29_balls.pHead)
			oldp0->p1 = 0;
		else
			g_vars->scene29_balls.field_8 = 0;

		oldhead->p0 = g_vars->scene29_balls.pTail;

		g_vars->scene29_balls.pTail = oldhead;
		g_vars->scene29_balls.numBalls--;

		if (!g_vars->scene29_balls.numBalls) {
			g_vars->scene29_balls.numBalls = 0;
			g_vars->scene29_balls.pTail = 0;
			g_vars->scene29_balls.field_8 = 0;
			g_vars->scene29_balls.pHead = 0;

			free(g_vars->scene29_balls.cPlex);
			g_vars->scene29_balls.cPlex = 0;
		}

		ani->show1(x, y, MV_SHG_NORM, 0);
		ani->_priority = 5;

		Ball *runPtr = g_vars->scene29_greenBalls.pTail;
		Ball *lastP = g_vars->scene29_greenBalls.field_8;

		if (!g_vars->scene29_greenBalls.pTail) {
			g_vars->scene29_greenBalls.cPlex = (byte *)calloc(g_vars->scene29_greenBalls.cPlexLen, sizeof(Ball));

			byte *p1 = g_vars->scene29_greenBalls.cPlex + (g_vars->scene29_greenBalls.cPlexLen - 1) * sizeof(Ball);

			if (g_vars->scene29_greenBalls.cPlexLen - 1 < 0) {
				runPtr = g_vars->scene29_greenBalls.pTail;
			} else {
				runPtr = g_vars->scene29_greenBalls.pTail;

				for (int j = 0; j < g_vars->scene29_greenBalls.cPlexLen; j++) {
					((Ball *)p1)->p1 = runPtr;
					runPtr = (Ball *)p1;

					p1 -= sizeof(Ball);
				}

				g_vars->scene29_greenBalls.pTail = runPtr;
			}
		}
		g_vars->scene29_greenBalls.pTail = runPtr->p0;
		runPtr->p1 = lastP;
		runPtr->p0 = 0;
		runPtr->ani = ani;

		g_vars->scene29_greenBalls.numBalls++;

		if (g_vars->scene29_greenBalls.field_8) {
			g_vars->scene29_greenBalls.field_8->p0 = runPtr;
			g_vars->scene29_greenBalls.field_8 = runPtr;
		} else {
			g_vars->scene29_greenBalls.pHead = runPtr;
			g_vars->scene29_greenBalls.field_8 = runPtr;
		}
	}
}

void sceneHandler29_shootRed() {
	if (g_vars->scene29_balls.numBalls) {
		int x = g_vars->scene29_shooter1->_ox - 101;
		int y = g_vars->scene29_shooter1->_oy - 14;
		StaticANIObject *ani = g_vars->scene29_balls.pHead->ani;
		Ball *oldhead = g_vars->scene29_balls.pHead;
		Ball *oldp0 = g_vars->scene29_balls.pHead->p0;

		g_vars->scene29_balls.pHead = g_vars->scene29_balls.pHead->p0;

		if (g_vars->scene29_balls.pHead)
			oldp0->p1 = 0;
		else
			g_vars->scene29_balls.field_8 = 0;

		oldhead->p0 = g_vars->scene29_balls.pTail;

		g_vars->scene29_balls.pTail = oldhead;
		g_vars->scene29_balls.numBalls--;

		if (!g_vars->scene29_balls.numBalls) {
			g_vars->scene29_balls.numBalls = 0;
			g_vars->scene29_balls.pTail = 0;
			g_vars->scene29_balls.field_8 = 0;
			g_vars->scene29_balls.pHead = 0;

			free(g_vars->scene29_balls.cPlex);
			g_vars->scene29_balls.cPlex = 0;
		}

		ani->show1(x, y, MV_SHR_NORM, 0);
		ani->_priority = 5;

		Ball *runPtr = g_vars->scene29_var07.pTail;
		Ball *lastP = g_vars->scene29_var07.field_8;

		if (!g_vars->scene29_var07.pTail) {
			g_vars->scene29_var07.cPlex = (byte *)calloc(g_vars->scene29_var07.cPlexLen, sizeof(Ball));

			byte *p1 = g_vars->scene29_var07.cPlex + (g_vars->scene29_var07.cPlexLen - 1) * sizeof(Ball);

			if (g_vars->scene29_var07.cPlexLen - 1 < 0) {
				runPtr = g_vars->scene29_var07.pTail;
			} else {
				runPtr = g_vars->scene29_var07.pTail;

				for (int j = 0; j < g_vars->scene29_var07.cPlexLen; j++) {
					((Ball *)p1)->p1 = runPtr;
					runPtr = (Ball *)p1;

					p1 -= sizeof(Ball);
				}

				g_vars->scene29_var07.pTail = runPtr;
			}
		}
		g_vars->scene29_var07.pTail = runPtr->p0;
		runPtr->p1 = lastP;
		runPtr->p0 = 0;
		runPtr->ani = ani;

		g_vars->scene29_var07.numBalls++;

		if (g_vars->scene29_var07.field_8) {
			g_vars->scene29_var07.field_8->p0 = runPtr;
			g_vars->scene29_var07.field_8 = runPtr;
		} else {
			g_vars->scene29_var07.pHead = runPtr;
			g_vars->scene29_var07.field_8 = runPtr;
		}
	}
}

void sceneHandler29_manJump() {
	if (!g_fp->_aniMan->_movement || g_fp->_aniMan->_movement->_id == MV_MAN29_RUN || g_fp->_aniMan->_movement->_id == MV_MAN29_STANDUP) {
		g_vars->scene29_var12 = 0;
		g_vars->scene29_var15 = 0;
		g_vars->scene29_var11 = 1;

		g_fp->_aniMan->changeStatics2(ST_MAN29_RUNR);
		g_fp->_aniMan->startAnim(MV_MAN29_JUMP, 0, -1);
	}

	g_vars->scene29_var20 = g_fp->_aniMan->_ox;
	g_vars->scene29_var21 = g_fp->_aniMan->_oy;
}

void sceneHandler29_manBend() {
	if (!g_fp->_aniMan->_movement || g_fp->_aniMan->_movement->_id == MV_MAN29_RUN || g_fp->_aniMan->_movement->_id == MV_MAN29_STANDUP) {
		g_vars->scene29_var12 = 0;
		g_vars->scene29_var15 = 0;
		g_vars->scene29_var11 = 1;

		g_fp->_aniMan->changeStatics2(ST_MAN29_RUNR);
		g_fp->_aniMan->startAnim(MV_MAN29_BEND, 0, -1);
	}

	g_vars->scene29_var20 = g_fp->_aniMan->_ox;
	g_vars->scene29_var21 = g_fp->_aniMan->_oy;
}

bool sceneHandler29_sub15(StaticANIObject *ani, int maxx) {
	if (!g_vars->scene29_var10 || g_vars->scene29_var15)
		return false;

	if ((ani->_ox >= g_vars->scene29_var20 + 42 || ani->_ox <= g_vars->scene29_var20 + 8)
		&& (ani->_ox < g_vars->scene29_var20 + 8 || maxx > g_vars->scene29_var20 + 27))
		return false;

	if (!g_fp->_aniMan->_movement)
		return true;

	int phase = g_fp->_aniMan->_movement->_currDynamicPhaseIndex;

	if (g_fp->_aniMan->_movement->_id != MV_MAN29_BEND && g_fp->_aniMan->_movement->_id != MV_MAN29_RUN
		&& (g_fp->_aniMan->_movement->_id != MV_MAN29_JUMP || (phase >= 3 && phase <= 6)))
		return false;
	else
		return true;
}

bool sceneHandler29_sub16(StaticANIObject *ani, int maxx) {
	if (!g_vars->scene29_var10 || g_vars->scene29_var15)
		return false;

	if (ani->_ox >= g_vars->scene29_var20 + 40) {
		if (maxx > g_vars->scene29_var20 + 27)
			return false;
	} else {
		if (ani->_ox <= g_vars->scene29_var20 + 10) {
			if (ani->_ox < g_vars->scene29_var20 + 40)
				return false;

			if (maxx > g_vars->scene29_var20 + 27)
				return false;
		}
	}

	if (!g_fp->_aniMan->_movement)
		return true;

	if (g_fp->_aniMan->_movement->_id == MV_MAN29_JUMP)
		return true;

	if (g_fp->_aniMan->_movement->_id == MV_MAN29_RUN)
		return true;

	if (g_fp->_aniMan->_movement->_id == MV_MAN29_BEND) {
		if (g_fp->_aniMan->_movement->_currDynamicPhaseIndex < 1 || g_fp->_aniMan->_movement->_currDynamicPhaseIndex > 5)
			return true;
	}

	return false;
}

void sceneHandler29_manHit() {
	MGMInfo mgminfo;

	g_vars->scene29_var15 = 1;

	g_fp->_aniMan->changeStatics2(ST_MAN29_RUNR);
	g_fp->_aniMan->setOXY(g_vars->scene29_var20, g_vars->scene29_var21);

	mgminfo.ani = g_fp->_aniMan;
	mgminfo.staticsId2 = ST_MAN29_SITR;
	mgminfo.y1 = 463;
	mgminfo.x1 = g_vars->scene29_var20 <= 638 ? 351 : 0;
	mgminfo.field_1C = 10;
	mgminfo.field_10 = 1;
	mgminfo.flags = (g_vars->scene29_var20 <= 638 ? 2 : 0) | 0x44;
	mgminfo.movementId = MV_MAN29_HIT;

	MessageQueue *mq = g_vars->scene29_mgm.genMovement(&mgminfo);
	ExCommand *ex;

	if (mq) {
		if (g_vars->scene29_var20 <= 638) {
			ex = new ExCommand(ANI_MAN, 1, MV_MAN29_STANDUP_NORM, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags = 2;
			ex->_keyCode = g_fp->_aniMan->_okeyCode;
			mq->addExCommandToEnd(ex);

			ex = new ExCommand(0, 17, MSG_SC29_STOPRIDE, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags = 2;
			mq->addExCommandToEnd(ex);

			g_vars->scene29_var09 = 0;
			g_vars->scene29_var10 = 0;
			g_vars->scene29_var11 = 0;
			g_vars->scene29_var12 = 0;
		} else {
			ex = new ExCommand(ANI_MAN, 1, MV_MAN29_STANDUP, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags = 2;
			ex->_keyCode = g_fp->_aniMan->_okeyCode;
			mq->addExCommandToEnd(ex);
		}

		mq->setFlags(mq->getFlags() | 1);

		if (!mq->chain(g_fp->_aniMan))
			delete mq;
	}
}

void sceneHandler29_assHitRed() {
	if (g_vars->scene29_ass->_statics->_staticsId == ST_ASS_NORM) {
		g_vars->scene29_ass->changeStatics2(ST_ASS_NORM);
		g_vars->scene29_ass->startAnim(MV_ASS_HITRED, 0, -1);
	}
}

void sceneHandler29_assHitGreen() {
	if (g_vars->scene29_ass->_statics->_staticsId == ST_ASS_NORM) {
		g_vars->scene29_ass->changeStatics2(ST_ASS_NORM);
		g_vars->scene29_ass->startAnim(MV_ASS_HITGREEN, 0, -1);
	}
}

void sceneHandler29_sub03() {
	Ball *ball = g_vars->scene29_greenBalls.pHead;
	Ball *newball;
	int x, y;

	while (ball) {
		x = ball->ani->_ox - 30;
		y = ball->ani->_oy;

		if (x >= 186) {
			if (sceneHandler29_sub16(ball->ani, x)) {
				newball = g_vars->scene29_balls.sub04(g_vars->scene29_balls.field_8, 0);
				newball->ani = ball->ani;

				if (g_vars->scene29_balls.field_8)
					g_vars->scene29_balls.field_8->p0 = newball;
				else
					g_vars->scene29_balls.pHead = newball;

				g_vars->scene29_balls.field_8 = newball;

				if (ball == g_vars->scene29_greenBalls.pHead)
					g_vars->scene29_greenBalls.pHead = ball->p0;
				else
					ball->p1->p0 = ball->p0;

				if (ball == g_vars->scene29_greenBalls.field_8)
					g_vars->scene29_greenBalls.field_8 = ball->p1;
				else
					ball->p0->p1 = ball->p1;

				g_vars->scene29_greenBalls.init(&ball);

				sceneHandler29_manHit();

				g_fp->playSound(SND_29_014, 0);

				ball->ani->startAnim(MV_SHG_HITMAN, 0, -1);

				g_vars->scene29_var18 = ball->ani->_id;
			} else {
				ball->ani->setOXY(x, y);
			}
		} else {
			newball = g_vars->scene29_balls.sub04(g_vars->scene29_balls.field_8, 0);
			newball->ani = ball->ani;

			if (g_vars->scene29_balls.field_8)
				g_vars->scene29_balls.field_8->p0 = newball;
			else
				g_vars->scene29_balls.pHead = newball;

			g_vars->scene29_balls.field_8 = newball;

			ball->ani->hide();

			if (ball == g_vars->scene29_greenBalls.pHead)
				g_vars->scene29_greenBalls.pHead = ball->p0;
			else
				ball->p1->p0 = ball->p0;

			if (ball == g_vars->scene29_greenBalls.field_8)
				g_vars->scene29_greenBalls.field_8 = ball->p1;
			else
				ball->p0->p1 = ball->p1;

			g_vars->scene29_greenBalls.init(&ball);

			sceneHandler29_assHitGreen();
		}

		ball = ball->p0;
	}

	ball = g_vars->scene29_var07.pHead;

	while (ball) {
		x = ball->ani->_ox - 30;
		y = ball->ani->_oy;

		if (x >= 147) {
			if (sceneHandler29_sub15(ball->ani, x)) {
				newball = g_vars->scene29_redBalls.sub04(g_vars->scene29_redBalls.field_8, 0);
				newball->ani = ball->ani;

				if (g_vars->scene29_redBalls.field_8)
					g_vars->scene29_redBalls.field_8->p0 = newball;
				else
					g_vars->scene29_redBalls.pHead = newball;

				g_vars->scene29_redBalls.field_8 = newball;

				g_vars->scene29_var07.sub05(ball);

				sceneHandler29_manHit();

				g_fp->playSound(SND_29_027, 0);

				ball->ani->startAnim(MV_SHR_HITMAN, 0, -1);

				g_vars->scene29_var18 = ball->ani->_id;
			} else {
				ball->ani->setOXY(x, y);
			}
		} else {
			newball = g_vars->scene29_redBalls.sub04(g_vars->scene29_redBalls.field_8, 0);
			newball->ani = ball->ani;

			if (g_vars->scene29_redBalls.field_8)
				g_vars->scene29_redBalls.field_8->p0 = newball;
			else
				g_vars->scene29_redBalls.pHead = newball;

			g_vars->scene29_redBalls.field_8 = newball;

			ball->ani->hide();

			if (ball == g_vars->scene29_var07.pHead)
				g_vars->scene29_var07.pHead = ball->p0;
			else
				ball->p1->p0 = ball->p0;

			if (ball == g_vars->scene29_var07.field_8)
				g_vars->scene29_var07.field_8 = ball->p1;
			else
				ball->p0->p1 = ball->p1;

			g_vars->scene29_var07.init(&ball);

			sceneHandler29_assHitRed();
		}

		ball = ball->p0;
	}
}

void sceneHandler29_manFromL() {
	if (g_vars->scene29_var20 < 497 && !g_vars->scene29_var17) {
		getCurrSceneSc2MotionController()->setEnabled();
		getGameLoaderInteractionController()->enableFlag24();

		g_fp->_aniMan->changeStatics2(ST_MAN_RIGHT | 0x4000);
		chainQueue(QU_SC29_MANFROM_L, 1);

		g_vars->scene29_var17 = 1;

		g_fp->_scrollSpeed = g_vars->scene29_var16;
	}
}

void sceneHandler29_manFromR() {
	getCurrSceneSc2MotionController()->setEnabled();
	getGameLoaderInteractionController()->enableFlag24();

	chainQueue(QU_SC29_MANFROM_R, 1);

	g_vars->scene29_var10 = 0;
	g_vars->scene29_var12 = 0;
}

int sceneHandler29_updateScreenCallback() {
	int res;

	res = g_fp->drawArcadeOverlay(g_vars->scene29_var10);

	if (!res)
		g_fp->_updateScreenCallback = 0;

	return res;
}

void sceneHandler29_manToL() {
	getCurrSceneSc2MotionController()->clearEnabled();
	getGameLoaderInteractionController()->disableFlag24();

	chainQueue(QU_SC29_MANTO_L, 1);

	g_vars->scene29_var10 = 1;

	g_vars->scene29_mgm.addItem(g_fp->_aniMan->_id);

	g_fp->_updateScreenCallback = sceneHandler29_updateScreenCallback;

	g_fp->_msgY = -1;
	g_fp->_msgX = -1;
}

void sceneHandler29_manToR() {
	getCurrSceneSc2MotionController()->clearEnabled();
	getGameLoaderInteractionController()->disableFlag24();

	chainQueue(QU_SC29_MANTO_R, 1);

	g_vars->scene29_var09 = 1;
	g_fp->_msgY = -1;
	g_fp->_msgX = -1;

	g_vars->scene29_var17 = 0;

	g_vars->scene29_var16 = g_fp->_scrollSpeed;
	g_fp->_scrollSpeed = 4;
}

void sceneHandler29_clickPorter(ExCommand *cmd) {
	if (!g_fp->_aniMan->isIdle() || g_fp->_aniMan->_flags & 0x100) {
		cmd->_messageKind = 0;

		return;
	}

	if (g_vars->scene29_var20 <= g_vars->scene29_porter->_ox) {
		if (ABS(351 - g_vars->scene29_var20) > 1 || ABS(443 - g_vars->scene29_var21) > 1
			|| g_fp->_aniMan->_movement || g_fp->_aniMan->_statics->_staticsId != ST_MAN_RIGHT) {
			if (g_fp->_msgX != 351 || g_fp->_msgY != 443) {
				MessageQueue *mq = getCurrSceneSc2MotionController()->method34(g_fp->_aniMan, 351, 443, 1, ST_MAN_RIGHT);

				if (mq) {
					mq->addExCommandToEnd(cmd->createClone());

					postExCommand(g_fp->_aniMan->_id, 2, 351, 443, 0, -1);
				}
			}
		} else {
			sceneHandler29_manToL();
		}
	} else {
		g_vars->scene29_var20 = g_fp->_aniMan->_ox;
		g_vars->scene29_var21 = g_fp->_aniMan->_oy;

		if (ABS(1582 - g_vars->scene29_var20) > 1 || ABS(445 - g_fp->_aniMan->_oy) > 1
			|| g_fp->_aniMan->_movement || g_fp->_aniMan->_statics->_staticsId != (0x4000 | ST_MAN_RIGHT)) {
			if (g_fp->_msgX != 1582 || g_fp->_msgY != 445) {
				MessageQueue *mq = getCurrSceneSc2MotionController()->method34(g_fp->_aniMan, 1582, 445, 1, (0x4000 | ST_MAN_RIGHT));

				if (mq) {
					mq->addExCommandToEnd(cmd->createClone());

					postExCommand(g_fp->_aniMan->_id, 2, 1582, 445, 0, -1);
				}
			}
		} else {
			sceneHandler29_manToR();
		}
	}
}

void sceneHandler29_sub05() {
	if (g_fp->_aniMan->_statics->_staticsId == ST_MAN29_RUNR) {
		if (g_vars->scene29_var20 > 1436) {
			sceneHandler29_manFromR();
		} else {
			g_vars->scene29_var14 = (1310 - g_vars->scene29_var20) * 5213 / 100000 + 25;

			if (!g_vars->scene29_var15)
				g_fp->_aniMan->startAnim(MV_MAN29_RUN, 0, -1);
		}
	}

	g_vars->scene29_var20 = g_fp->_aniMan->_ox;
	g_vars->scene29_var21 = g_fp->_aniMan->_oy;
}

void sceneHandler29_shootersEscape() {
	if (g_vars->scene29_var10) {
		g_vars->scene29_var20 += 2;

		g_fp->_aniMan->setOXY(g_vars->scene29_var20, g_vars->scene29_var21);

		if (g_vars->scene29_var20 > 1310 && !g_vars->scene29_shooter1->_movement && !g_vars->scene29_shooter2->_movement
			&& g_vars->scene29_shooter1->_statics->_staticsId == ST_STR1_RIGHT) {
			g_vars->scene29_var13 = 0;

			g_vars->scene29_shooter1->changeStatics2(ST_STR1_STAND);
			g_vars->scene29_shooter2->changeStatics2(ST_STR2_STAND);

			chainQueue(QU_SC29_ESCAPE, 1);

			g_vars->scene29_ass->queueMessageQueue(0);
			g_vars->scene29_ass->hide();

			g_fp->setObjectState(sO_LeftPipe_29, g_fp->getObjectEnumState(sO_LeftPipe_29, sO_IsOpened));
		}
	} else if (g_vars->scene29_var09) {
		g_vars->scene29_var20 -= 4;

		g_fp->_aniMan->setOXY(g_vars->scene29_var20, g_vars->scene29_var21);
	}
}

void sceneHandler29_sub07() {
	g_vars->scene29_var20 -= 2;
  
	g_fp->_aniMan->setOXY(g_vars->scene29_var20, g_vars->scene29_var21);
}

void sceneHandler29_shoot() {
	if (g_vars->scene29_var10 && g_vars->scene29_var20 < 1310) {
		if (g_fp->_rnd->getRandomNumber(1) || g_vars->scene29_shooter1->_movement || g_vars->scene29_shooter1->_statics->_staticsId != ST_STR1_RIGHT) {
			if (!g_vars->scene29_shooter2->_movement && g_vars->scene29_shooter2->_statics->_staticsId == ST_STR2_RIGHT) {
				if (g_vars->scene29_shooter2->_flags & 4) {
					g_vars->scene29_shooter2->startAnim(MV_STR2_SHOOT, 0, -1);

					g_vars->scene29_var13 = 0;
				}
			}
		} else {
			g_vars->scene29_shooter1->startAnim(MV_STR1_SHOOT, 0, -1);

			g_vars->scene29_var13 = 0;
		}
	}
}

void sceneHandler29_animBearded() {
	MessageQueue *mq;

	for (uint i = 0; i < g_vars->scene29_var19.size(); i++) {
		StaticANIObject *ani = g_vars->scene29_var19[i]->ani;

		if (g_vars->scene29_var19[i]->wbflag) {
			int x = ani->_ox;
			int y = ani->_oy;

			if (!ani->_movement && ani->_statics->_staticsId == (ST_BRDCMN_RIGHT | 0x4000)) {
				x -= 4;

				if (x - g_vars->scene29_var20 < 100 || !g_vars->scene29_var10) {
					mq = new MessageQueue(g_fp->_currentScene->getMessageQueueById(QU_SC29_BRDOUT1), 0, 1);

					mq->replaceKeyCode(-1, ani->_okeyCode);
					mq->chain(0);

					g_vars->scene29_var19[i]->wbflag = 0;
					g_vars->scene29_var19[i]->wbcounter = 0;
				}
			}

			if (!ani->_movement && ani->_statics->_staticsId == ST_BRDCMN_GOR)
				ani->startAnim(MV_BRDCMN_GOR, 0, -1);

			if (ani->_movement) {
				if (ani->_movement->_id == MV_BRDCMN_GOR) {
					x -= 4;

					if (g_vars->scene29_var20 - x < 60 || x - g_vars->scene29_var20 < -260 || !g_vars->scene29_var10) {
						ani->changeStatics2(ST_BRDCMN_RIGHT);

						mq = new MessageQueue(g_fp->_currentScene->getMessageQueueById(QU_SC29_BRDOUT2), 0, 1);

						mq->replaceKeyCode(-1, ani->_okeyCode);
						mq->chain(0);

						g_vars->scene29_var19[i]->wbflag = 0;
						g_vars->scene29_var19[i]->wbcounter = 0;
					}
				}
			}

			ani->setOXY(x, y);
			continue;
		}

		if (g_vars->scene29_var10 && g_vars->scene29_var19[i]->wbcounter > 30) {
			int newx;

			if (g_fp->_rnd->getRandomNumber(1))
				goto dostuff;

			if (g_vars->scene29_var20 <= 700) {
				g_vars->scene29_var19[i]->wbcounter++;
				continue;
			}

			if (g_vars->scene29_var20 >= 1100) {
			dostuff:
				if (g_vars->scene29_var20 <= 700 || g_vars->scene29_var20 >= 1350) {
					g_vars->scene29_var19[i]->wbcounter++;
					continue;
				}

				mq = new MessageQueue(g_fp->_currentScene->getMessageQueueById(QU_SC29_BRD2), 0, 1);

				newx = g_vars->scene29_var20 - 200;
			} else {
				mq = new MessageQueue(g_fp->_currentScene->getMessageQueueById(QU_SC29_BRD1), 0, 1);

				newx = g_vars->scene29_var20 + 350;
			}

			mq->getExCommandByIndex(0)->_x = newx;
			mq->replaceKeyCode(-1, ani->_okeyCode);
			mq->chain(0);

			g_vars->scene29_var19[i]->wbflag = 1;
			g_vars->scene29_var19[i]->wbcounter = 0;
		}

		g_vars->scene29_var19[i]->wbcounter++;
	}
}



int sceneHandler29(ExCommand *cmd) {
	if (cmd->_messageKind != 17)
		return 0;

	switch (cmd->_messageNum) {
	case MSG_CMN_WINARCADE:
		sceneHandler29_winArcade();
		break;

	case MSG_SC29_LAUGH:
		if (g_vars->scene29_var18 == ANI_SHELL_GREEN) {
			g_fp->playSound(SND_29_028, 0);
			break;
		}

		g_fp->playSound(SND_29_029, 0);

		break;

	case MSG_SC29_SHOWLASTRED:
		if (g_vars->scene29_balls.numBalls) {
			g_vars->scene29_redBalls.field_8->ani->show1(-1, -1, -1, 0);
			g_vars->scene29_redBalls.field_8->ani->startAnim(MV_SHR_HITASS, 0, -1);
		}

		break;

	case MSG_SC29_SHOOTGREEN:
		sceneHandler29_shootGreen();
		break;

	case MSG_SC29_SHOOTRED:
		sceneHandler29_shootRed();
		break;

	case MSG_SC29_SHOWLASTGREEN:
		if (g_vars->scene29_balls.numBalls) {
			g_vars->scene29_balls.field_8->ani->show1(-1, -1, -1, 0);
			g_vars->scene29_balls.field_8->ani->startAnim(MV_SHG_HITASS, 0, -1);
		}

		break;

	case MSG_SC29_STOPRIDE:
		g_vars->scene29_var09 = 0;
		g_vars->scene29_var10 = 0;
		g_vars->scene29_var11 = 0;
		g_vars->scene29_var12 = 0;

		getCurrSceneSc2MotionController()->setEnabled();
		getGameLoaderInteractionController()->enableFlag24();
		break;

	case MSG_SC29_DISABLERIDEBACK:
		g_vars->scene29_var12 = 0;
		break;

	case MSG_SC29_ENABLERIDEBACK:
		g_vars->scene29_var12 = 1;
		g_vars->scene29_var11 = 0;
		break;

	case MSG_SC29_DISABLEPORTER:
		g_vars->scene29_var11 = 0;
		break;

	case MSG_SC29_ENABLEPORTER:
		g_vars->scene29_var11 = 1;
		g_vars->scene29_var12 = 0;
		g_vars->scene29_var15 = 0;
		break;

	case 29:
		if (!g_vars->scene29_var09 || g_vars->scene29_var10) {
			if (!g_vars->scene29_var10) {
				StaticANIObject *ani = g_fp->_currentScene->getStaticANIObjectAtPos(g_fp->_sceneRect.left + cmd->_x, g_fp->_sceneRect.top + cmd->_y);

				if (ani && ani == g_vars->scene29_porter) {
					sceneHandler29_clickPorter(cmd);

					cmd->_messageKind = 0;
					break;
				}
				break;
			}

			sceneHandler29_manJump();

			cmd->_messageKind = 0;
			break;
		}
		break;

	case 107:
		if (g_vars->scene29_var10)
			sceneHandler29_manBend();

		break;

	case 33:
		if (g_vars->scene29_var10) {
			if (g_vars->scene29_var20 > g_fp->_sceneRect.right - 500)
				g_fp->_currentScene->_x = g_fp->_sceneRect.right - g_vars->scene29_var20 - 350;

			if (g_vars->scene29_var20 < g_fp->_sceneRect.left + 100)
				g_fp->_currentScene->_x = g_vars->scene29_var20 - g_fp->_sceneRect.left - 100;

		} else if (g_fp->_aniMan2) {
			int x = g_fp->_aniMan2->_ox;

			if (x < g_fp->_sceneRect.left + 300)
				g_fp->_currentScene->_x = x - 400 - g_fp->_sceneRect.left;

			if (x > g_fp->_sceneRect.right - 300)
				g_fp->_currentScene->_x = x + 400 - g_fp->_sceneRect.right;
		}

		g_vars->scene29_var20 = g_fp->_aniMan->_ox;
		g_vars->scene29_var21 = g_fp->_aniMan->_oy;

		sceneHandler29_sub03();

		if (!g_vars->scene29_porter->_movement)
			g_vars->scene29_porter->startAnim(MV_PTR_MOVEFAST, 0, -1);

		if (g_vars->scene29_var09)
			sceneHandler29_manFromL();
		else if (g_vars->scene29_var10 && !g_fp->_aniMan->_movement)
			sceneHandler29_sub05();

		if (g_vars->scene29_var11)
			sceneHandler29_shootersEscape();
		else if (g_vars->scene29_var12)
			sceneHandler29_sub07();

		g_vars->scene29_var13++;

		if (g_vars->scene29_var13 > g_vars->scene29_var14)
			sceneHandler29_shoot();

		sceneHandler29_animBearded();

		g_fp->_behaviorManager->updateBehaviors();
		g_fp->startSceneTrack();

		break;
	}

	return 0;
}

int scene29_updateCursor() {
	g_fp->updateCursorCommon();

	if (g_vars->scene29_var10) {
		if (g_fp->_cursorId != PIC_CSR_DEFAULT_INV && g_fp->_cursorId != PIC_CSR_ITN_INV)
			g_fp->_cursorId = -1;
	} else if (g_vars->scene29_var09) {
		if (g_fp->_cursorId != PIC_CSR_DEFAULT_INV && g_fp->_cursorId != PIC_CSR_ITN_INV)
			g_fp->_cursorId = PIC_CSR_DEFAULT;
	} else if (g_fp->_objectIdAtCursor == ANI_PORTER) {
		if (g_fp->_cursorId == PIC_CSR_DEFAULT)
			g_fp->_cursorId = PIC_CSR_ITN;
	} else {
		if (g_fp->_objectIdAtCursor == PIC_SC29_LTRUBA && g_fp->_cursorId == PIC_CSR_ITN)
			g_fp->_cursorId = PIC_CSR_GOL;
	}
	return g_fp->_cursorId;
}

} // End of namespace Fullpipe