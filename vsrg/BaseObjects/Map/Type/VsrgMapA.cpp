#include "stdafx.h" 
#include "VsrgMapA.h"
#include <iostream>

VsrgMapA::VsrgMapA() {}
VsrgMapA::~VsrgMapA() {}

SPtrHitObjectVector VsrgMapA::getHitObjectVector() const {
	return ho_v_;
}

SPtrEventObjectVector VsrgMapA::getEventObjectVector() const {
	return eo_v_;
}

void VsrgMapA::setHitObjectVector(const SPtrHitObjectVector & ho_v) {
	ho_v_ = ho_v;
}

void VsrgMapA::setEventObjectVector(const SPtrEventObjectVector & eo_v) {
	eo_v_ = eo_v;
}
