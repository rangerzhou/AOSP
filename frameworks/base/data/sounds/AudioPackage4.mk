#
# Audio Package 4
#
# Include this file in a product makefile to include these audio files
#
# This is a larger package of sounds than the 1.0 release for devices
# that have larger internal flash.
#

LOCAL_PATH:= frameworks/base/data/sounds

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/F1_MissedCall.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/F1_MissedCall.ogg \
	$(LOCAL_PATH)/F1_New_MMS.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/F1_New_MMS.ogg \
	$(LOCAL_PATH)/F1_New_SMS.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/F1_New_SMS.ogg \
	$(LOCAL_PATH)/Alarm_Buzzer.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/alarms/Alarm_Buzzer.ogg \
	$(LOCAL_PATH)/Alarm_Beep_01.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/alarms/Alarm_Beep_01.ogg \
	$(LOCAL_PATH)/Alarm_Beep_02.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/alarms/Alarm_Beep_02.ogg \
	$(LOCAL_PATH)/Alarm_Classic.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/alarms/Alarm_Classic.ogg \
	$(LOCAL_PATH)/Alarm_Beep_03.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/alarms/Alarm_Beep_03.ogg \
	$(LOCAL_PATH)/Alarm_Rooster_02.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/alarms/Alarm_Rooster_02.ogg \
	$(LOCAL_PATH)/notifications/Beat_Box_Android.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Beat_Box_Android.ogg \
	$(LOCAL_PATH)/notifications/Cricket.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Cricket.ogg \
	$(LOCAL_PATH)/notifications/Doink.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Doink.ogg \
	$(LOCAL_PATH)/notifications/Drip.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Drip.ogg \
	$(LOCAL_PATH)/notifications/Heaven.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Heaven.ogg \
	$(LOCAL_PATH)/notifications/SpaceSeed.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/SpaceSeed.ogg \
	$(LOCAL_PATH)/notifications/TaDa.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/TaDa.ogg \
	$(LOCAL_PATH)/notifications/Tinkerbell.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Tinkerbell.ogg \
	$(LOCAL_PATH)/notifications/moonbeam.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/moonbeam.ogg \
	$(LOCAL_PATH)/notifications/pixiedust.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/pixiedust.ogg \
	$(LOCAL_PATH)/notifications/pizzicato.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/pizzicato.ogg \
	$(LOCAL_PATH)/notifications/Plastic_Pipe.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Plastic_Pipe.ogg \
	$(LOCAL_PATH)/notifications/tweeters.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/tweeters.ogg \
	$(LOCAL_PATH)/effects/Effect_Tick.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/Effect_Tick.ogg \
	$(LOCAL_PATH)/effects/KeypressStandard.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/KeypressStandard.ogg \
	$(LOCAL_PATH)/effects/KeypressSpacebar.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/KeypressSpacebar.ogg \
	$(LOCAL_PATH)/effects/KeypressDelete.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/KeypressDelete.ogg \
	$(LOCAL_PATH)/effects/KeypressInvalid.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/KeypressInvalid.ogg \
	$(LOCAL_PATH)/effects/KeypressReturn.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/KeypressReturn.ogg \
	$(LOCAL_PATH)/effects/VideoRecord.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/VideoRecord.ogg \
	$(LOCAL_PATH)/effects/VideoStop.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/VideoStop.ogg \
	$(LOCAL_PATH)/effects/camera_click.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/camera_click.ogg \
	$(LOCAL_PATH)/effects/LowBattery.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/LowBattery.ogg \
	$(LOCAL_PATH)/effects/Dock.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/Dock.ogg \
	$(LOCAL_PATH)/effects/Undock.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/Undock.ogg \
	$(LOCAL_PATH)/effects/Lock.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/Lock.ogg \
	$(LOCAL_PATH)/effects/Unlock.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/Unlock.ogg \
	$(LOCAL_PATH)/effects/ogg/Trusted.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ui/Trusted.ogg \
	$(LOCAL_PATH)/Ring_Classic_02.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Ring_Classic_02.ogg \
	$(LOCAL_PATH)/Ring_Digital_02.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Ring_Digital_02.ogg \
	$(LOCAL_PATH)/Ring_Synth_04.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Ring_Synth_04.ogg \
	$(LOCAL_PATH)/Ring_Synth_02.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Ring_Synth_02.ogg \
	$(LOCAL_PATH)/ringtones/FreeFlight.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/FreeFlight.ogg \
	$(LOCAL_PATH)/newwavelabs/Backroad.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Backroad.ogg \
	$(LOCAL_PATH)/newwavelabs/CaffeineSnake.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/CaffeineSnake.ogg

ifneq ($(MINIMAL_NEWWAVELABS),true)
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/newwavelabs/DearDeer.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/DearDeer.ogg \
	$(LOCAL_PATH)/newwavelabs/DontPanic.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/DontPanic.ogg \
	$(LOCAL_PATH)/newwavelabs/Highwire.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Highwire.ogg \
	$(LOCAL_PATH)/newwavelabs/KzurbSonar.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/KzurbSonar.ogg \
	$(LOCAL_PATH)/newwavelabs/OnTheHunt.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/OnTheHunt.ogg \
	$(LOCAL_PATH)/newwavelabs/Voila.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/notifications/Voila.ogg \
	$(LOCAL_PATH)/newwavelabs/Big_Easy.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Big_Easy.ogg \
	$(LOCAL_PATH)/newwavelabs/BirdLoop.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/BirdLoop.ogg \
	$(LOCAL_PATH)/newwavelabs/Bollywood.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Bollywood.ogg \
	$(LOCAL_PATH)/newwavelabs/BussaMove.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/BussaMove.ogg \
	$(LOCAL_PATH)/newwavelabs/Cairo.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Cairo.ogg \
	$(LOCAL_PATH)/newwavelabs/Calypso_Steel.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Calypso_Steel.ogg \
	$(LOCAL_PATH)/newwavelabs/Champagne_Edition.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Champagne_Edition.ogg \
	$(LOCAL_PATH)/newwavelabs/Club_Cubano.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Club_Cubano.ogg \
	$(LOCAL_PATH)/newwavelabs/CrayonRock.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/CrayonRock.ogg \
	$(LOCAL_PATH)/newwavelabs/CurveBall.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/CurveBall.ogg \
	$(LOCAL_PATH)/newwavelabs/DancinFool.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/DancinFool.ogg \
	$(LOCAL_PATH)/newwavelabs/Ding.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Ding.ogg \
	$(LOCAL_PATH)/newwavelabs/DonMessWivIt.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/DonMessWivIt.ogg \
	$(LOCAL_PATH)/newwavelabs/Eastern_Sky.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Eastern_Sky.ogg \
	$(LOCAL_PATH)/newwavelabs/Enter_the_Nexus.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Enter_the_Nexus.ogg \
	$(LOCAL_PATH)/newwavelabs/EtherShake.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/EtherShake.ogg \
	$(LOCAL_PATH)/newwavelabs/Funk_Yall.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Funk_Yall.ogg \
	$(LOCAL_PATH)/newwavelabs/Gimme_Mo_Town.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Gimme_Mo_Town.ogg \
	$(LOCAL_PATH)/newwavelabs/Glacial_Groove.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Glacial_Groove.ogg \
	$(LOCAL_PATH)/newwavelabs/Growl.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Growl.ogg \
	$(LOCAL_PATH)/newwavelabs/HalfwayHome.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/HalfwayHome.ogg \
	$(LOCAL_PATH)/newwavelabs/LoopyLounge.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/LoopyLounge.ogg \
	$(LOCAL_PATH)/newwavelabs/LoveFlute.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/LoveFlute.ogg \
	$(LOCAL_PATH)/newwavelabs/MidEvilJaunt.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/MidEvilJaunt.ogg \
	$(LOCAL_PATH)/newwavelabs/MildlyAlarming.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/MildlyAlarming.ogg \
	$(LOCAL_PATH)/newwavelabs/Nairobi.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Nairobi.ogg \
	$(LOCAL_PATH)/newwavelabs/Nassau.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Nassau.ogg \
	$(LOCAL_PATH)/newwavelabs/No_Limits.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/No_Limits.ogg \
	$(LOCAL_PATH)/newwavelabs/OrganDub.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/OrganDub.ogg \
	$(LOCAL_PATH)/newwavelabs/Paradise_Island.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Paradise_Island.ogg \
	$(LOCAL_PATH)/newwavelabs/Playa.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Playa.ogg \
	$(LOCAL_PATH)/newwavelabs/Road_Trip.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Road_Trip.ogg \
	$(LOCAL_PATH)/newwavelabs/Safari.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Safari.ogg \
	$(LOCAL_PATH)/newwavelabs/Seville.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Seville.ogg \
	$(LOCAL_PATH)/newwavelabs/Shes_All_That.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Shes_All_That.ogg \
	$(LOCAL_PATH)/newwavelabs/SilkyWay.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/SilkyWay.ogg \
	$(LOCAL_PATH)/newwavelabs/Steppin_Out.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Steppin_Out.ogg \
	$(LOCAL_PATH)/newwavelabs/Terminated.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Terminated.ogg \
	$(LOCAL_PATH)/newwavelabs/Third_Eye.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/Third_Eye.ogg \
	$(LOCAL_PATH)/newwavelabs/TwirlAway.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/TwirlAway.ogg \
	$(LOCAL_PATH)/newwavelabs/World.ogg:$(TARGET_COPY_OUT_PRODUCT)/media/audio/ringtones/World.ogg
endif
