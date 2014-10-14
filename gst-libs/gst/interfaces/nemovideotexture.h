/*
 * Copyright (C) 2013 Jolla LTD.
 *
 * Contact: Mohammed Hassan <mohammed.hassan@jollamobile.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __NEMO_GST_VIDEO_TEXTURE_H__
#define __NEMO_GST_VIDEO_TEXTURE_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define NEMO_GST_TYPE_VIDEO_TEXTURE \
  (nemo_gst_video_texture_get_type ())
#define NEMO_GST_VIDEO_TEXTURE(obj) \
  (GST_IMPLEMENTS_INTERFACE_CHECK_INSTANCE_CAST ((obj), NEMO_GST_TYPE_VIDEO_TEXTURE, \
                                                 NemoGstVideoTexture))
#define NEMO_GST_VIDEO_TEXTURE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), NEMO_GST_TYPE_VIDEO_TEXTURE, NemoGstVideoTextureClass))
#define NEMO_GST_IS_VIDEO_TEXTURE(obj) \
  (GST_IMPLEMENTS_INTERFACE_CHECK_INSTANCE_TYPE ((obj), NEMO_GST_TYPE_VIDEO_TEXTURE))
#define NEMO_GST_IS_VIDEO_TEXTURE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), NEMO_GST_TYPE_VIDEO_TEXTURE))
#define NEMO_GST_VIDEO_TEXTURE_GET_CLASS(inst) \
  (G_TYPE_INSTANCE_GET_INTERFACE ((inst), NEMO_GST_TYPE_VIDEO_TEXTURE, NemoGstVideoTextureClass))

typedef void * EGLImageKHR;
typedef void * EGLSyncKHR;
typedef void * EGLDisplay;

typedef struct _NemoGstVideoTexture NemoGstVideoTexture;
typedef struct _NemoGstVideoTextureClass NemoGstVideoTextureClass;
typedef struct _NemoGstVideoTextureFrameInfo NemoGstVideoTextureFrameInfo;

struct _NemoGstVideoTextureFrameInfo
{
  GstClockTime timestamp;
  GstClockTime duration;
  guint64 offset;
  guint64 offset_end;
  gpointer _gst_reserved[GST_PADDING];
};

struct _NemoGstVideoTextureClass
{
  GTypeInterface parent_klass;

  /* interface methods */
  gboolean (* acquire_frame) (NemoGstVideoTexture *iface);
  gboolean (* bind_frame) (NemoGstVideoTexture *iface, EGLImageKHR *image);
  void (* unbind_frame) (NemoGstVideoTexture *iface);
  void (* release_frame) (NemoGstVideoTexture *iface, EGLSyncKHR sync);
  gboolean (* get_frame_info) (NemoGstVideoTexture *iface, NemoGstVideoTextureFrameInfo *info);
  const GstStructure *(* get_frame_qdata)(NemoGstVideoTexture *iface, const GQuark quark);
  void (* attach_to_display) (NemoGstVideoTexture *iface, EGLDisplay dpy);
  void (* detach_from_display) (NemoGstVideoTexture *iface);

  /*< private >*/
  gpointer                 _gst_reserved[GST_PADDING];
};

GType   nemo_gst_video_texture_get_type          (void);

/* virtual class function wrappers */

gboolean nemo_gst_video_texture_acquire_frame (NemoGstVideoTexture *iface);
gboolean nemo_gst_video_texture_bind_frame (NemoGstVideoTexture *iface, EGLImageKHR *image);
void     nemo_gst_video_texture_unbind_frame (NemoGstVideoTexture *iface);
void     nemo_gst_video_texture_release_frame (NemoGstVideoTexture *iface, EGLSyncKHR sync);
gboolean nemo_gst_video_texture_get_frame_info (NemoGstVideoTexture *iface, NemoGstVideoTextureFrameInfo *info);
const GstStructure *nemo_gst_video_texture_get_frame_qdata (NemoGstVideoTexture *iface, const GQuark quark);
void    nemo_gst_video_texture_attach_to_display(NemoGstVideoTexture *iface, EGLDisplay dpy);
void    nemo_gst_video_texture_detach_from_display(NemoGstVideoTexture *iface);

/* trigger signals */
void     nemo_gst_video_texture_frame_ready (NemoGstVideoTexture *iface, gint frame);

G_END_DECLS

#endif /* __NEMO_GST_VIDEO_TEXTURE_H__ */
