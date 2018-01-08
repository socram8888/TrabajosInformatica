package es.uv.videlsol.valenbisi;

import android.app.Service;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;

/**
 * Created by alumno on 21/02/2017.
 */
public class StopListAdapter extends BaseAdapter {

    private final List<StopInfo> stops;
    private final Context context;

    static class ViewHolder {
        TextView number;
        TextView address;
        TextView reports;
    }

    public StopListAdapter(Context c, StopDatabase db) {
        context = c;
        stops = db.list();
    }

    @Override
    public int getCount() {
        return stops.size();
    }

    @Override
    public Object getItem(int position) {
        return stops.get(position);
    }

    @Override
    public long getItemId(int position) {
        return stops.get(position).getNumber();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder = null;

        if (convertView == null) { // Si es null la creamos a partir de layout
            LayoutInflater li = (LayoutInflater) context.getSystemService(Service.LAYOUT_INFLATER_SERVICE);
            convertView = li.inflate(R.layout.stop_list_entry, null);

            holder = new ViewHolder();
            holder.number = (TextView) convertView.findViewById(R.id.stop_entry_id);
            holder.address = (TextView) convertView.findViewById(R.id.stop_entry_address);
            holder.reports = (TextView) convertView.findViewById(R.id.stop_entry_reports);
            convertView.setTag(holder);
        } else {
            // Si no es null la reutilizamos para actualizarla
            holder = (ViewHolder) convertView.getTag();
        }

        StopInfo p = stops.get(position);
        holder.address.setText(p.getAddress());
        holder.number.setText(context.getResources().getString(R.string.stop_id) + ": " + p.getNumber());
        holder.reports.setText(context.getResources().getString(R.string.report_count) + ": " + '0');

        return convertView;
    }
}
