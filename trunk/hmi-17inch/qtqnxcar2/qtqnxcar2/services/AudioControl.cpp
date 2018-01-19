#include "AudioControl.h"
#include "AudioControl_p.h"

#include <qpps/changeset.h>

#include <QDebug>
#include <QJsonDocument>

namespace QnxCar {

//static const char* pps_speakerVolumeKey = "output.speaker.volume";
//static const char* pps_handsetVolumeKey = "output.handset.volume";
//static const char* pps_outputAvailableKey = "output.available";
//static const char* pps_balanceKey = "balance";
//static const char* pps_bassKey = "bass";
//static const char* pps_fadeKey = "fade";
static const char* pps_midKey = "mid";
//static const char* pps_trebleKey = "treble";
static snd_mixer_t *mixer_handle;
static int card = 0;
static int dev = 0;
/**
static AudioControl::DeviceType deviceFromString(const QString &s)
{
    if (s == QStringLiteral("handset"))
        return AudioControl::Handset;
    if (s == QStringLiteral("speaker"))
        return AudioControl::Speaker;

    qWarning("%s: Unexpected output device '%s'", Q_FUNC_INFO, qPrintable(s));
    Q_ASSERT(!"unhandled device type");
    return AudioControl::Speaker;
}
**/
AudioControl::Private::Private(AudioControl *qq)
    : QObject(qq)
    , q(qq)
    , m_ppsMixerObject(0)
    , m_ppsStatusObject(0)
    , m_ppsControlObject(0)
    , m_ppsVolumeObject(0)
    , m_balance(50.0)
    , m_bass(74.0)
    , m_fade(42.0)
    , m_mid(92.0)
    , m_treble(79.0)
    , m_currentOutputDevice(AudioControl::Speaker)
{
    int rtn = 0;
    if ((rtn = snd_mixer_open (&mixer_handle, card, dev)) < 0)
    {
        fprintf (stderr, "snd_mixer_open failed: %s\n", snd_strerror (rtn));
    }

    int     rtnvolume;
    snd_mixer_group_t group;

    memset (&group, 0, sizeof (group));
    strcpy(group.gid.name,"Pri Mixer");
    if ((rtnvolume = snd_mixer_group_read (mixer_handle, &group)) < 0)
    {
        if (rtnvolume != EOK)
        {
            fprintf (stderr, "snd_mixer_group_read failed: %s\n", snd_strerror (rtnvolume));
        }
    }
    m_speakerVolume =  (double)((group.volume.values[0] - group.min)*100/(group.max-group.min));
    qDebug() << "volume:" << m_speakerVolume << group.volume.values[0];
    m_handsetVolume = m_speakerVolume;
     connectCurrentOutputVolumeChanged();
    /*
    //balance
    snd_mixer_element_t element;
    snd_mixer_element_info_t element_info;
    snd_mixer_element_pan_control1_range_t range;
    int32_t		pan[5] ={ 0 };
    int rtnbalance = 0;
    memset(&element, 0, sizeof(snd_mixer_element_t));
    memset(&element_info, 0, sizeof(snd_mixer_element_info_t));
    memset(&range, 0, sizeof(snd_mixer_element_pan_control1_range_t));

    element.eid.type = SND_MIXER_ETYPE_PAN_CONTROL1;
    strcpy(element.eid.name,"Playback Balance");
    element.data.pc1.pan = 1;
    element.data.pc1.pan_over = 0;
    element.data.pc1.pan_size = 1;
    element.data.pc1.ppan = pan;

    element_info.data.pc1.prange = &range;
    strcpy(element_info.eid.name,"Playback Balance");
    element_info.eid.type = SND_MIXER_ETYPE_PAN_CONTROL1;

    element_info.data.pc1.prange->pan_type = SND_MIXER_PAN_LEFT_RIGHT;

    if((rtnbalance = snd_mixer_element_info (mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info failed: %s\n", snd_strerror (rtnbalance));
    }
    if((rtnbalance = snd_mixer_element_info_build(mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info_build failed: %s\n", snd_strerror (rtnbalance));
    }
    m_balance  = (double)(element.data.pc1.ppan[0]);
    //m_bass
    snd_mixer_element_t element;
    snd_mixer_element_info_t element_info;
    int rtnbass = 0;
    memset(&element, 0, sizeof(snd_mixer_element_t));
    memset(&element_info, 0, sizeof(snd_mixer_element_info_t));

    element.eid.type = SND_MIXER_ETYPE_TONE_CONTROL1;
    element.data.tc1.tc |= SND_MIXER_TC1_BASS;
    strcpy( element.eid.name,"Tone Control");
    element_info.eid.type = SND_MIXER_ETYPE_TONE_CONTROL1;
    strcpy( element_info.eid.name,"Tone Control");
    if((rtnbass = snd_mixer_element_info (mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info failed: %s\n", snd_strerror (rtnbass));
        return false;
    }
   m_bass  = (double)(element.data.tc1.treble);
*/
}

bool AudioControl::Private::setVolumeService(snd_mixer_t *mixer_handle,const char *group_name,int value)
{
    int     rtn;
    int     j = 0;
    snd_mixer_group_t group;

    memset (&group, 0, sizeof (group));

    //group.gid.name = group_name;
    if(strlen(group_name) >32)
        return false;
    strcpy(group.gid.name,group_name);
    if ((rtn = snd_mixer_group_read (mixer_handle, &group)) < 0)
    {
        if (rtn != EOK)
        {
            fprintf (stderr, "snd_mixer_group_read failed: %s\n", snd_strerror (rtn));
            return false;
        }
    }
    value = (value * (group.max - group.min)) / 100 + group.min;
    if (value > group.max)
        value = group.max;
    if (value < group.min)
        value = group.min;
    for (j = 0; j <= SND_MIXER_CHN_LAST; j++)
    {
        group.volume.values[j] = value;
    }
    if ((rtn = snd_mixer_group_write (mixer_handle, &group)) < 0)
    {
        fprintf (stderr, "snd_mixer_group_write failed: %s\n", snd_strerror (rtn));
        return false;
    }

    return true;

}
bool AudioControl::Private::setVolume(const QString &output, double volume)
{
    bool setvolumetmp = false;

    setvolumetmp = setVolumeService(mixer_handle,"Pri Mixer",(int)volume);
    return setvolumetmp;
}

void AudioControl::Private::connectCurrentOutputVolumeChanged()
{
    disconnect(q, &AudioControl::speakerVolumeChanged, q, &AudioControl::currentOutputVolumeChanged);
    disconnect(q, &AudioControl::handsetVolumeChanged, q, &AudioControl::currentOutputVolumeChanged);
    switch (m_currentOutputDevice) {
    case Speaker:
        connect(q, &AudioControl::speakerVolumeChanged, q, &AudioControl::currentOutputVolumeChanged);
        break;
    case Handset:
        connect(q, &AudioControl::handsetVolumeChanged, q, &AudioControl::currentOutputVolumeChanged);
        break;
    }
}

void AudioControl::Private::setCurrentOutputDevice(DeviceType type)
{
    if (m_currentOutputDevice == type)
        return;
    m_currentOutputDevice = type;
    connectCurrentOutputVolumeChanged();
    emit q->currentOutputDeviceChanged(m_currentOutputDevice);
    emit q->currentOutputVolumeChanged(q->currentOutputVolume());
}

AudioControl::AudioControl(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

double AudioControl::speakerVolume() const
{
    return d->m_speakerVolume;
}

void AudioControl::setSpeakerVolume(double rawVolume)
{
    const double volume = qBound(0.0, rawVolume, 100.0);

    if (qFuzzyCompare(d->m_speakerVolume, volume))
        return;

    bool tmpsetvolume = d->setVolume(QStringLiteral("speaker"), volume);
    if(!tmpsetvolume)
        return;
    //printf("set volume success volume %d\n",(int)volume);
    d->m_speakerVolume = volume;
    emit speakerVolumeChanged(d->m_speakerVolume);
}

double AudioControl::handsetVolume() const
{
    return d->m_handsetVolume;
}

void AudioControl::setHandsetVolume(double rawVolume)
{
    const double volume = qBound(0.0, rawVolume, 100.0);

    if (qFuzzyCompare(d->m_handsetVolume, volume))
        return;
    d->setVolume(QStringLiteral("handset"), volume);
    d->m_handsetVolume = volume;
    emit handsetVolumeChanged(d->m_handsetVolume);
}

double AudioControl::currentOutputVolume() const
{
    switch (d->m_currentOutputDevice) {
    case Speaker:
        return d->m_speakerVolume;
    case Handset:
        return d->m_handsetVolume;
    }

    Q_ASSERT(!"unhandled device type");

    return 0;
}

void AudioControl::setCurrentOutputVolume(double volume)
{
    switch (d->m_currentOutputDevice) {
    case Speaker:
        setSpeakerVolume(volume);
        break;
    case Handset:
        setHandsetVolume(volume);
        break;
    }
}

double AudioControl::balance() const
{
    return d->m_balance;
}

bool AudioControl::setBalanceService(snd_mixer_t * mixer_handle,  int value)
{
    snd_mixer_element_t element;
    snd_mixer_element_info_t element_info;
    snd_mixer_element_pan_control1_range_t range;
    int32_t		pan[5] ={ 0 };
    int rtn = 0;
    memset(&element, 0, sizeof(snd_mixer_element_t));
    memset(&element_info, 0, sizeof(snd_mixer_element_info_t));
    memset(&range, 0, sizeof(snd_mixer_element_pan_control1_range_t));

    element.eid.type = SND_MIXER_ETYPE_PAN_CONTROL1;
    //memcpy(element.eid.name,"Playback Balance",sizeof("Playback Balance"));
    strcpy(element.eid.name,"Playback Balance");
    element.data.pc1.pan = 1;
    element.data.pc1.pan_over = 0;
    element.data.pc1.pan_size = 1;
    element.data.pc1.ppan = pan;

    element_info.data.pc1.prange = &range;
    //memcpy(element_info.eid.name,"Playback Balance",sizeof("Playback Balance"));
    strcpy(element_info.eid.name,"Playback Balance");
    element_info.eid.type = SND_MIXER_ETYPE_PAN_CONTROL1;

    element_info.data.pc1.prange->pan_type = SND_MIXER_PAN_LEFT_RIGHT;

    if((rtn = snd_mixer_element_info (mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info failed: %s\n", snd_strerror (rtn));
    }
    if((rtn = snd_mixer_element_info_build(mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info_build failed: %s\n", snd_strerror (rtn));
    }

    value = (value * (element_info.data.pc1.prange->max- element_info.data.pc1.prange->min)) / 100 + element_info.data.pc1.prange->min;

    if (value > element_info.data.pc1.prange->max )
        value = element_info.data.pc1.prange->max ;
    if (value < element_info.data.pc1.prange->min)
        value = element_info.data.pc1.prange->min;

    element.data.pc1.ppan[0] = value;
    if ((rtn = snd_mixer_element_write (mixer_handle, &element)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_write failed: %s\n", snd_strerror (rtn));
        return false;
    }

    return true;
}
void AudioControl::setBalance(double rawBalance)
{

    const double balance = qBound(0.0, rawBalance, 100.0);

    if (qFuzzyCompare(d->m_balance, balance))
        return;
    /*
    if (!d->m_ppsMixerObject->setAttribute(QString::fromLatin1(pps_balanceKey), QPps::Variant(balance))) {
        qWarning() << "AudioControl: unable to write back 'balance'";
        return;
    }
*/
    bool setbalcancetmp = setBalanceService(mixer_handle,(int)balance);
    if(!setbalcancetmp)
        return;
    d->m_balance = balance;
    emit balanceChanged(d->m_balance);
}

double AudioControl::bass() const
{
    return d->m_bass;
}
bool AudioControl::setBassService(snd_mixer_t * mixer_handle,int value)
{
    snd_mixer_element_t element;
    snd_mixer_element_info_t element_info;
    int rtn = 0;
    memset(&element, 0, sizeof(snd_mixer_element_t));
    memset(&element_info, 0, sizeof(snd_mixer_element_info_t));

    element.eid.type = SND_MIXER_ETYPE_TONE_CONTROL1;
    element.data.tc1.tc |= SND_MIXER_TC1_BASS;
    strcpy( element.eid.name,"Tone Control");
    element_info.eid.type = SND_MIXER_ETYPE_TONE_CONTROL1;
    strcpy( element_info.eid.name,"Tone Control");
    if((rtn = snd_mixer_element_info (mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info failed: %s\n", snd_strerror (rtn));
        return false;
    }
    value = (value * (element_info.data.tc1.max_bass - element_info.data.tc1.min_bass)) / 100 +
            element_info.data.tc1.min_bass;

    if (value > element_info.data.tc1.max_bass )
        value = element_info.data.tc1.max_bass ;
    if (value < element_info.data.tc1.min_bass)
        value = element_info.data.tc1.min_bass;

    element.data.tc1.treble = value;
    if ((rtn = snd_mixer_element_write (mixer_handle, &element)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_write failed: %s\n", snd_strerror (rtn));
        return false;
    }
    return true;
}
void AudioControl::setBass(double rawBass)
{
    const double bass = qBound(0.0, rawBass, 100.0);

    if (qFuzzyCompare(d->m_bass, bass))
        return;

    bool setbassservicetmp = setBassService(mixer_handle,bass);
    setbassservicetmp = false;

    /*
    if (!d->m_ppsMixerObject->setAttribute(QString::fromLatin1(pps_bassKey), QPps::Variant(bass))) {
        qWarning() << "AudioControl: unable to write back 'bass'";
        return;
    }
    */
    if(setbassservicetmp)
        d->m_bass = bass;
    else
        printf("set bass fail\n");
    emit bassChanged(d->m_bass);
}

double AudioControl::fade() const
{
    return d->m_fade;
}

bool AudioControl::setFaderService(snd_mixer_t * mixer_handle,  int value)
{
    snd_mixer_element_t element;
    snd_mixer_element_info_t element_info;
    snd_mixer_element_pan_control1_range_t range;
    int32_t		pan[5] ={ 0 };
    int rtn = 0;
    memset(&element, 0, sizeof(snd_mixer_element_t));
    memset(&element_info, 0, sizeof(snd_mixer_element_info_t));
    memset(&range, 0, sizeof(snd_mixer_element_pan_control1_range_t));

    element.eid.type = SND_MIXER_ETYPE_PAN_CONTROL1;
    strcpy(element.eid.name,"Playback Fader");

    element.data.pc1.pan = 1;
    element.data.pc1.pan_over = 0;
    element.data.pc1.pan_size = 1;
    element.data.pc1.ppan = pan;

    element_info.data.pc1.prange = &range;
    strcpy(element_info.eid.name,"Playback Fader");
    element_info.eid.type = SND_MIXER_ETYPE_PAN_CONTROL1;

    element_info.data.pc1.prange->pan_type = SND_MIXER_PAN_FRONT_REAR;

    if((rtn = snd_mixer_element_info (mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info failed: %s\n", snd_strerror (rtn));
    }
    if((rtn = snd_mixer_element_info_build(mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info_build failed: %s\n", snd_strerror (rtn));
    }

    value = (value * (element_info.data.pc1.prange->max- element_info.data.pc1.prange->min)) / 100 + element_info.data.pc1.prange->min;

    if (value > element_info.data.pc1.prange->max )
        value = element_info.data.pc1.prange->max ;
    if (value < element_info.data.pc1.prange->min)
        value = element_info.data.pc1.prange->min;

    element.data.pc1.ppan[0] = value;
    if ((rtn = snd_mixer_element_write (mixer_handle, &element)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_write failed: %s\n", snd_strerror (rtn));
        return false;
    }
    return true;
}
void AudioControl::setFade(double rawFade)
{
    const double fade = qBound(0.0, rawFade, 100.0);

    if (qFuzzyCompare(d->m_fade, fade))
        return;
    /*
    if (!d->m_ppsMixerObject->setAttribute(QString::fromLatin1(pps_fadeKey), QPps::Variant(fade))) {
        qWarning() << "AudioControl: unable to write back 'fade'";
        return;
    }
    */
    bool setfadetmp = setFaderService(mixer_handle,(int)fade);
    if(!setfadetmp)
        // return;
        d->m_fade = fade;
    emit fadeChanged(d->m_fade);
}

double AudioControl::mid() const
{
    return d->m_mid;
}

void AudioControl::setMid(double rawMid)
{
    const double mid = qBound(0.0, rawMid, 100.0);

    if (qFuzzyCompare(d->m_mid, mid))
        return;

    if (!d->m_ppsMixerObject->setAttribute(QString::fromLatin1(pps_midKey), QPps::Variant(mid))) {
        qWarning() << "AudioControl: unable to write back 'mid'";
        return;
    }

    d->m_mid = mid;
    emit midChanged(d->m_mid);
}

double AudioControl::treble() const
{
    return d->m_treble;
}

bool AudioControl::setTrebleService(snd_mixer_t * mixer_handle,int value)
{
    snd_mixer_element_t element;
    snd_mixer_element_info_t element_info;
    int rtn = 0;
    memset(&element, 0, sizeof(snd_mixer_element_t));
    memset(&element_info, 0, sizeof(snd_mixer_element_info_t));

    element.eid.type = SND_MIXER_ETYPE_TONE_CONTROL1;
    element.data.tc1.tc |= SND_MIXER_TC1_TREBLE;
    strcpy(element.eid.name,"Tone Control");

    element_info.eid.type = SND_MIXER_ETYPE_TONE_CONTROL1;
    strcpy(element_info.eid.name,"Tone Control");

    if((rtn = snd_mixer_element_info (mixer_handle, &element_info)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_info failed: %s\n", snd_strerror (rtn));
        return false;
    }
    value = (value * (element_info.data.tc1.max_treble - element_info.data.tc1.min_treble)) / 100 +
            element_info.data.tc1.min_treble;

    if (value > element_info.data.tc1.max_treble )
        value = element_info.data.tc1.max_treble ;
    if (value < element_info.data.tc1.min_treble)
        value = element_info.data.tc1.min_treble;

    element.data.tc1.treble = value;
    if ((rtn = snd_mixer_element_write (mixer_handle, &element)) < 0)
    {
        fprintf (stderr, "snd_mixer_element_write failed: %s\n", snd_strerror (rtn));
        return false;
    }
    return true;
}
void AudioControl::setTreble(double rawTreble)
{
    const double treble = qBound(0.0, rawTreble, 100.0);

    if (qFuzzyCompare(d->m_treble, treble))
        return;
    bool settrebletmp = setTrebleService(mixer_handle,treble);
    if(!settrebletmp)
        return;
    /*
    if (!d->m_ppsMixerObject->setAttribute(QString::fromLatin1(pps_trebleKey), QPps::Variant(treble)))     {
        qWarning() << "AudioControl: unable to write back 'treble'";
        return;
    }
*/
    d->m_treble = treble;
    emit trebleChanged(d->m_treble);
}

AudioControl::DeviceType AudioControl::currentOutputDevice() const
{
    return d->m_currentOutputDevice;
}

}
