// Fill out your copyright notice in the Description page of Project Settings.


#include "FogHUDWidget.h"
#include "HealthBarWidget.h"

void UFogHUDWidget::SetHealthPercent(float Percent)
{
	if (WBP_HealthBar)
	{
		WBP_HealthBar->SetHealthPercent(Percent);
	}
}
